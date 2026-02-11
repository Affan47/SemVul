verifyNoDeadCode(Function &F) {
  for (auto &B : F) {
    for (auto &I : B) {
      if (isInstructionTriviallyDead(&I)) {
        std::string ErrMessage;
        raw_string_ostream RSO(ErrMessage);
        RSO << "Dead instruction detected!\n" << I << "\n";
        llvm_unreachable(RSO.str().c_str());
      }
    }
  }
}
