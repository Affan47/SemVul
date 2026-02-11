next_frag_pre_opcode_bytes (const fragS *fragp)
{
  const fragS *next_fragp = fragp->fr_next;
  xtensa_opcode next_opcode;

  if (!next_frag_opcode_is_loop (fragp, &next_opcode))
    return 0;


  while (next_fragp->fr_fix == 0)
    next_fragp = next_fragp->fr_next;

  if (next_fragp->fr_type != rs_machine_dependent)
    return 0;


  if (next_fragp->tc_frag_data.slot_subtypes[0] > RELAX_IMMED)
      return get_expanded_loop_offset (next_opcode) + RELAXED_LOOP_INSN_BYTES;

  return 0;
}
