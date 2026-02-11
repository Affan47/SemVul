check_loop_free(const char *name,
		       cssc_delta_table* t,
		       seq_no starting_seq,
		       std::vector<bool>& loopfree,
		       std::vector<bool>& seen)
  {
    bool ok = true;
    const seq_no highest_seqno = t->highest_seqno();
    seq_no lowest_dirty_seq = highest_seqno;

    std::vector<bool>::iterator i;


    for (seq_no s=starting_seq;
	 s;
	 s = t->delta_at_seq(s).prev_seq())
      {
	if (s < lowest_dirty_seq)
	  lowest_dirty_seq = s;

	if (loopfree[s])
	  {
	    break;
	  }
	else if (seen[s])
	  {
	    errormsg("%s: loop in predecessors at sequence number %u\n",
		     name, (unsigned)s);
	    ok = false;
	    break;
	  }
	else
	  {
	    seen[s] = true;
	  }
      }


    if (ok)
      {
	for (seq_no s=starting_seq;
	     s;
	     s = t->delta_at_seq(s).prev_seq())
	  {
	    if (loopfree[s])
	      break;
	    else if (seen[s])
	      loopfree[s] = true;
	  }
      }
    for (i = seen.begin()+lowest_dirty_seq; i != seen.end(); ++i)
      *i = false;

    return ok;
  }
}
