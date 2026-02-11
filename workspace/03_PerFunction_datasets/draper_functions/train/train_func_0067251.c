getIDWithAttrMask(uint16_t* instructionID,
                             struct InternalInstruction* insn,
                             uint16_t attrMask) {
  bool hasModRMExtension;

  InstructionContext instructionClass = contextForAttrs(attrMask);

  hasModRMExtension = modRMRequired(insn->opcodeType,
                                    instructionClass,
                                    insn->opcode);

  if (hasModRMExtension) {
    if (readModRM(insn))
      return -1;

    *instructionID = decode(insn->opcodeType,
                            instructionClass,
                            insn->opcode,
                            insn->modRM);
  } else {
    *instructionID = decode(insn->opcodeType,
                            instructionClass,
                            insn->opcode,
                            0);
  }

  return 0;
}
