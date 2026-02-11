insert_phi_node (regno, bb)
     int regno, bb;
{
  basic_block b = BASIC_BLOCK (bb);
  edge e;
  int npred, i;
  rtvec vec;
  rtx phi, reg;
  rtx insn;
  int end_p;


  for (e = b->pred, npred = 0; e; e = e->pred_next)
    if (e->src != ENTRY_BLOCK_PTR)
      npred++;


  if (npred == 0)
    return;


  reg = regno_reg_rtx[regno];


  vec = rtvec_alloc (npred * 2);
  for (e = b->pred, i = 0; e ; e = e->pred_next, i += 2)
    if (e->src != ENTRY_BLOCK_PTR)
      {
	RTVEC_ELT (vec, i + 0) = pc_rtx;
	RTVEC_ELT (vec, i + 1) = GEN_INT (e->src->index);
      }

  phi = gen_rtx_PHI (VOIDmode, vec);
  phi = gen_rtx_SET (VOIDmode, reg, phi);

  insn = first_insn_after_basic_block_note (b);
  end_p = PREV_INSN (insn) == b->end;
  emit_insn_before (phi, insn);
  if (end_p)
    b->end = PREV_INSN (insn);
}
