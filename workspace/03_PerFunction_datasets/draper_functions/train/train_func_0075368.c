readOpcodeModifier(struct InternalInstruction* insn) {
  dbgprintf(insn, "readOpcodeModifier()");

  if (insn->consumedOpcodeModifier)
    return 0;

  insn->consumedOpcodeModifier = TRUE;

  switch (insn->spec->modifierType) {
  default:
    debug("Unknown modifier type.");
    return -1;
  case MODIFIER_NONE:
    debug("No modifier but an operand expects one.");
    return -1;
  case MODIFIER_OPCODE:
    insn->opcodeModifier = insn->opcode - insn->spec->modifierBase;
    return 0;
  case MODIFIER_MODRM:
    insn->opcodeModifier = insn->modRM - insn->spec->modifierBase;
    return 0;
  }
}
