readImmediate(struct InternalInstruction* insn, uint8_t size) {
  uint8_t imm8;
  uint16_t imm16;
  uint32_t imm32;
  uint64_t imm64;

  dbgprintf(insn, "readImmediate()");

  if (insn->numImmediatesConsumed == 2) {
    debug("Already consumed two immediates");
    return -1;
  }

  if (size == 0)
    size = insn->immediateSize;
  else
    insn->immediateSize = size;

  switch (size) {
  case 1:
    if (consumeByte(insn, &imm8))
      return -1;
    insn->immediates[insn->numImmediatesConsumed] = imm8;
    break;
  case 2:
    if (consumeUInt16(insn, &imm16))
      return -1;
    insn->immediates[insn->numImmediatesConsumed] = imm16;
    break;
  case 4:
    if (consumeUInt32(insn, &imm32))
      return -1;
    insn->immediates[insn->numImmediatesConsumed] = imm32;
    break;
  case 8:
    if (consumeUInt64(insn, &imm64))
      return -1;
    insn->immediates[insn->numImmediatesConsumed] = imm64;
    break;
  }

  insn->numImmediatesConsumed++;

  return 0;
}
