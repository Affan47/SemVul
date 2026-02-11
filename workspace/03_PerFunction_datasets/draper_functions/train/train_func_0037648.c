clear_arc_insns_equiv_num (state)
     state_t state;
{
  arc_t arc;

  for (arc = first_out_arc (state); arc != NULL; arc = next_out_arc (arc))
    {
      arc->insn->insn_reserv_decl->equiv_class_num = 0;
      arc->insn->insn_reserv_decl->state_alts = 0;
    }
}
