dump_new_block_header (int i, basic_block bb, rtx head, rtx tail)
{
  if (!i)
    fprintf (sched_dump,
	     ";;   ======================================================\n");
  else
    fprintf (sched_dump,
	     ";;   =====================ADVANCING TO=====================\n");
  fprintf (sched_dump,
	   ";;   -- basic block %d from %d to %d -- %s reload\n",
	   bb->index, INSN_UID (head), INSN_UID (tail),
	   (reload_completed ? "after" : "before"));
  fprintf (sched_dump,
	   ";;   ======================================================\n");
  fprintf (sched_dump, "\n");
}
