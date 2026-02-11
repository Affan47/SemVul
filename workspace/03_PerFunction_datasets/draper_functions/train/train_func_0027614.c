CheckBothSmi(Register first, Register second) {
  if (first.is(second)) {
    return CheckSmi(first);
  }
  STATIC_ASSERT(kSmiTag == 0 && kHeapObjectTag == 1 && kHeapObjectTagMask == 3);
  leal(kScratchRegister, Operand(first, second, times_1, 0));
  testb(kScratchRegister, Immediate(0x03));
  return zero;
}
