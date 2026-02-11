init_call_opcodes (void)
{
  if (callx0_op == XTENSA_UNDEFINED)
    {
      callx0_op  = xtensa_opcode_lookup (xtensa_default_isa, "callx0");
      callx4_op  = xtensa_opcode_lookup (xtensa_default_isa, "callx4");
      callx8_op  = xtensa_opcode_lookup (xtensa_default_isa, "callx8");
      callx12_op = xtensa_opcode_lookup (xtensa_default_isa, "callx12");
      call0_op   = xtensa_opcode_lookup (xtensa_default_isa, "call0");
      call4_op   = xtensa_opcode_lookup (xtensa_default_isa, "call4");
      call8_op   = xtensa_opcode_lookup (xtensa_default_isa, "call8");
      call12_op  = xtensa_opcode_lookup (xtensa_default_isa, "call12");
    }
}
