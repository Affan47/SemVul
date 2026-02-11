loop_delete_insns (rtx first, rtx last)
{
  while (1)
    {
      if (loop_dump_stream)
	fprintf (loop_dump_stream, ", deleting init_insn (%d)",
		 INSN_UID (first));
      delete_insn (first);


      if (first == last)
	break;

      first = NEXT_INSN (first);
    }
}
