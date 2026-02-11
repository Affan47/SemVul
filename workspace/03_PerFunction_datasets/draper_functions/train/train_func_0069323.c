tidy_fallthru_edge (edge e, basic_block b, basic_block c)
{
  rtx q;


  for (q = NEXT_INSN (BB_END (b)); q != BB_HEAD (c); q = NEXT_INSN (q))
    if (INSN_P (q))
      return;


  q = BB_END (b);
  if (GET_CODE (q) == JUMP_INSN
      && onlyjump_p (q)
      && (any_uncondjump_p (q)
	  || (b->succ == e && e->succ_next == NULL)))
    {
#ifdef HAVE_cc0


      if (any_condjump_p (q) && only_sets_cc0_p (PREV_INSN (q)))
	q = PREV_INSN (q);
#endif

      q = PREV_INSN (q);


      while (GET_CODE (q) == NOTE && NOTE_LINE_NUMBER (q) >= 0)
	q = PREV_INSN (q);
    }


  if (q != PREV_INSN (BB_HEAD (c)))
    delete_insn_chain (NEXT_INSN (q), PREV_INSN (BB_HEAD (c)));

  e->flags |= EDGE_FALLTHRU;
}
