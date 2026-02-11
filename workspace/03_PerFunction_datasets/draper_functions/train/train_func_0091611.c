debug_dependencies (rtx head, rtx tail)
{
  rtx insn;
  rtx next_tail = NEXT_INSN (tail);

  fprintf (sched_dump, ";;   %7s%6s%6s%6s%6s%6s%14s\n",
	   "insn", "code", "bb", "dep", "prio", "cost",
	   "reservation");
  fprintf (sched_dump, ";;   %7s%6s%6s%6s%6s%6s%14s\n",
	   "----", "----", "--", "---", "----", "----",
	   "-----------");

  for (insn = head; insn != next_tail; insn = NEXT_INSN (insn))
    {
      if (! INSN_P (insn))
	{
	  int n;
	  fprintf (sched_dump, ";;   %6d ", INSN_UID (insn));
	  if (NOTE_P (insn))
	    {
	      n = NOTE_KIND (insn);
	      fprintf (sched_dump, "%s\n", GET_NOTE_INSN_NAME (n));
	    }
	  else
	    fprintf (sched_dump, " {%s}\n", GET_RTX_NAME (GET_CODE (insn)));
	  continue;
	}

      fprintf (sched_dump,
	       ";;   %s%5d%6d%6d%6d%6d%6d   ",
	       (SCHED_GROUP_P (insn) ? "+" : " "),
	       INSN_UID (insn),
	       INSN_CODE (insn),
	       BLOCK_NUM (insn),
	       sched_emulate_haifa_p ? -1 : sd_lists_size (insn, SD_LIST_BACK),
	       (sel_sched_p () ? (sched_emulate_haifa_p ? -1
			       : INSN_PRIORITY (insn))
		: INSN_PRIORITY (insn)),
	       (sel_sched_p () ? (sched_emulate_haifa_p ? -1
			       : insn_cost (insn))
		: insn_cost (insn)));

      if (recog_memoized (insn) < 0)
	fprintf (sched_dump, "nothing");
      else
	print_reservation (sched_dump, insn);

      fprintf (sched_dump, "\t: ");
      {
	sd_iterator_def sd_it;
	dep_t dep;

	FOR_EACH_DEP (insn, SD_LIST_FORW, sd_it, dep)
	  fprintf (sched_dump, "%d ", INSN_UID (DEP_CON (dep)));
      }
      fprintf (sched_dump, "\n");
    }

  fprintf (sched_dump, "\n");
}
