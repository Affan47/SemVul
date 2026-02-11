getLowestPossibleValue(IRBuilder<> &IRB, Value *A, Value *Sa,
                                bool isSigned) {
    if (isSigned) {

      Value *SaOtherBits = IRB.CreateLShr(IRB.CreateShl(Sa, 1), 1);
      Value *SaSignBit = IRB.CreateXor(Sa, SaOtherBits);

      return
        IRB.CreateOr(IRB.CreateAnd(A, IRB.CreateNot(SaOtherBits)), SaSignBit);
    } else {

      return IRB.CreateAnd(A, IRB.CreateNot(Sa));
    }
  }
