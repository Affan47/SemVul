CCAssignFnForRet(CallingConv::ID CC,
                                          bool isTaillCall) {
  if (Subtarget->is64Bit()) {
    if (Subtarget->isTargetWin64())
      return RetCC_X86_Win64_C;
    else
      return RetCC_X86_64_C;
  }

  return RetCC_X86_32_C;
}
