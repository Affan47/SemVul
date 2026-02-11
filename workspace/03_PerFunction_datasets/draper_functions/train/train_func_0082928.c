num_loop_insns (struct loop *loop)
{
  basic_block *bbs, bb;
  unsigned i, ninsns = 0;
  rtx insn;

  bbs = get_loop_body (loop);
  for (i = 0; i < loop->num_nodes; i++)
    {
      bb = bbs[i];
      ninsns++;
      for (insn = BB_HEAD (bb); insn != BB_END (bb); insn = NEXT_INSN (insn))
	if (INSN_P (insn))
	  ninsns++;
    }
  free(bbs);

  return ninsns;
}
