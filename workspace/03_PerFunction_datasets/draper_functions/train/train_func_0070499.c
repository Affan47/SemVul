swap_callx_for_call_opcode (xtensa_opcode opcode)
{
  init_call_opcodes ();

  if (opcode == callx0_op) return call0_op;
  if (opcode == callx4_op) return call4_op;
  if (opcode == callx8_op) return call8_op;
  if (opcode == callx12_op) return call12_op;


  return XTENSA_UNDEFINED;
}
