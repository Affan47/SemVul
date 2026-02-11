rmdel(sid id)
{
  if (!edit_mode_ok(true))
    return false;

  delta *d = find_delta(id);
  if (0 == d)
    {
      errormsg("%s: Specified SID not found in SCCS file.", name.c_str());
      return false;
    }
  const seq_no seq = d->seq();

  const_delta_iterator iter(delta_table);
  while (iter.next())
    {
      if (iter->prev_seq() == seq)
	{
	  errormsg("%s: Specified SID has a successor.", name.c_str());
	  return false;
	}
      if (is_seqlist_member(seq, iter->get_included_seqnos())
	  || is_seqlist_member(seq, iter->get_excluded_seqnos())
	  || is_seqlist_member(seq, iter->get_ignored_seqnos()))
	{
	  errormsg("%s: Specified SID is used in another delta.",
	       name.c_str());
	  return false;
	}
    }

  d->set_type('R');

  FILE *out = start_update();
  if (NULL == out)
    return false;

  if (write(out))
    {
      xfile_error("Write error.");
      return false;
    }

  update_state state = COPY;
  char c;

  bool retval = true;

  while (read_line(&c))
    {
      if (0 != c)
	{
	  check_arg();
	  if (strict_atous(plinebuf->c_str() + 3) == seq)
	    {
	      if (!next_state(state, c))
		{
		  corrupt("Unexpected control line");
		  retval = false;
		  break;
		}
	    }
	  else if (state == INSERT)
	    {
	      corrupt("Non-terminal delta!?!");
	      retval = false;
	      break;
	    }
	  else
	    {
	      fputs(plinebuf->c_str(), out);
	      putc('\n', out);
	    }
	}
      else if (state != INSERT)
	{
	  fputs(plinebuf->c_str(), out);
	  putc('\n', out);
	}
    }


  if (state != COPY)
    {
      corrupt("Unexpected EOF");
      return false;
    }

  if (true == retval)
    {
      retval = end_update(&out);
    }
  return retval;
}
