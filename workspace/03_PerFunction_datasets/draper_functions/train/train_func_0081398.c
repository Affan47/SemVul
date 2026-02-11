LeaveExitFrame(bool save_doubles) {


  if (save_doubles) {
    int offset = -2 * kPointerSize;
    for (int i = 0; i < XMMRegister::kNumAllocatableRegisters; i++) {
      XMMRegister reg = XMMRegister::FromAllocationIndex(i);
      movsd(reg, Operand(rbp, offset - ((i + 1) * kDoubleSize)));
    }
  }

  movq(rcx, Operand(rbp, 1 * kPointerSize));
  movq(rbp, Operand(rbp, 0 * kPointerSize));


  lea(rsp, Operand(r12, 1 * kPointerSize));


  push(rcx);

  LeaveExitFrameEpilogue();
}
