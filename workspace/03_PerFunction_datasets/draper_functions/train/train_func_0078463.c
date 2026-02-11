biv_elimination_giv_has_0_offset (struct induction *biv,
				  struct induction *giv, rtx insn)
{


  if (giv->auto_inc_opt
      && ((loop_insn_first_p (giv->insn, insn)
	   && loop_insn_first_p (insn, biv->insn))
	  || (loop_insn_first_p (biv->insn, insn)
	      && loop_insn_first_p (insn, giv->insn))))
    return 0;

  return 1;
}
