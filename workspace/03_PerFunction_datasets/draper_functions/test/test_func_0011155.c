readSIB(struct InternalInstruction* insn) {
  SIBIndex sibIndexBase = 0;
  SIBBase sibBaseBase = 0;
  uint8_t index, base;

  dbgprintf(insn, "readSIB()");

  if (insn->consumedSIB)
    return 0;

  insn->consumedSIB = TRUE;

  switch (insn->addressSize) {
  case 2:
    dbgprintf(insn, "SIB-based addressing doesn't work in 16-bit mode");
    return -1;
    break;
  case 4:
    sibIndexBase = SIB_INDEX_EAX;
    sibBaseBase = SIB_BASE_EAX;
    break;
  case 8:
    sibIndexBase = SIB_INDEX_RAX;
    sibBaseBase = SIB_BASE_RAX;
    break;
  }

  if (consumeByte(insn, &insn->sib))
    return -1;

  index = indexFromSIB(insn->sib) | (xFromREX(insn->rexPrefix) << 3);

  switch (index) {
  case 0x4:
    insn->sibIndex = SIB_INDEX_NONE;
    break;
  default:
    insn->sibIndex = (SIBIndex)(sibIndexBase + index);
    if (insn->sibIndex == SIB_INDEX_sib ||
        insn->sibIndex == SIB_INDEX_sib64)
      insn->sibIndex = SIB_INDEX_NONE;
    break;
  }

  switch (scaleFromSIB(insn->sib)) {
  case 0:
    insn->sibScale = 1;
    break;
  case 1:
    insn->sibScale = 2;
    break;
  case 2:
    insn->sibScale = 4;
    break;
  case 3:
    insn->sibScale = 8;
    break;
  }

  base = baseFromSIB(insn->sib) | (bFromREX(insn->rexPrefix) << 3);

  switch (base) {
  case 0x5:
    switch (modFromModRM(insn->modRM)) {
    case 0x0:
      insn->eaDisplacement = EA_DISP_32;
      insn->sibBase = SIB_BASE_NONE;
      break;
    case 0x1:
      insn->eaDisplacement = EA_DISP_8;
      insn->sibBase = (insn->addressSize == 4 ?
                       SIB_BASE_EBP : SIB_BASE_RBP);
      break;
    case 0x2:
      insn->eaDisplacement = EA_DISP_32;
      insn->sibBase = (insn->addressSize == 4 ?
                       SIB_BASE_EBP : SIB_BASE_RBP);
      break;
    case 0x3:
      debug("Cannot have Mod = 0b11 and a SIB byte");
      return -1;
    }
    break;
  default:
    insn->sibBase = (SIBBase)(sibBaseBase + base);
    break;
  }

  return 0;
}
