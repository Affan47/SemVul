decode(OpcodeType type,
                       InstructionContext insnContext,
                       uint8_t opcode,
                       uint8_t modRM) {
  const struct ModRMDecision* dec;

  switch (type) {
  default:
    debug("Unknown opcode type");
    return 0;
  case ONEBYTE:
    dec = &ONEBYTE_SYM.opcodeDecisions[insnContext].modRMDecisions[opcode];
    break;
  case TWOBYTE:
    dec = &TWOBYTE_SYM.opcodeDecisions[insnContext].modRMDecisions[opcode];
    break;
  case THREEBYTE_38:
    dec = &THREEBYTE38_SYM.opcodeDecisions[insnContext].modRMDecisions[opcode];
    break;
  case THREEBYTE_3A:
    dec = &THREEBYTE3A_SYM.opcodeDecisions[insnContext].modRMDecisions[opcode];
    break;
  case THREEBYTE_A6:
    dec = &THREEBYTEA6_SYM.opcodeDecisions[insnContext].modRMDecisions[opcode];
    break;
  case THREEBYTE_A7:
    dec = &THREEBYTEA7_SYM.opcodeDecisions[insnContext].modRMDecisions[opcode];
    break;
  }

  switch (dec->modrm_type) {
  default:
    debug("Corrupt table!  Unknown modrm_type");
    return 0;
  case MODRM_ONEENTRY:
    return dec->instructionIDs[0];
  case MODRM_SPLITRM:
    if (modFromModRM(modRM) == 0x3)
      return dec->instructionIDs[1];
    else
      return dec->instructionIDs[0];
  case MODRM_FULL:
    return dec->instructionIDs[modRM];
  }
}
