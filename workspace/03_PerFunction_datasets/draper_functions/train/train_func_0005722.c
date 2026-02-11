dump_insn_vector (rtx_vec_t succs)
{
  int i;
  rtx succ;

  FOR_EACH_VEC_ELT (succs, i, succ)
    if (succ)
      dump_insn (succ);
    else
      sel_print ("NULL ");
}
