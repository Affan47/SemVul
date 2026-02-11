findBaseConstants() {

  std::sort(ConstCandVec.begin(), ConstCandVec.end(),
            [](const ConstantCandidate &LHS, const ConstantCandidate &RHS) {
    if (LHS.ConstInt->getType() != RHS.ConstInt->getType())
      return LHS.ConstInt->getType()->getBitWidth() <
             RHS.ConstInt->getType()->getBitWidth();
    return LHS.ConstInt->getValue().ult(RHS.ConstInt->getValue());
  });


  auto MinValItr = ConstCandVec.begin();
  for (auto CC = std::next(ConstCandVec.begin()), E = ConstCandVec.end();
       CC != E; ++CC) {
    if (MinValItr->ConstInt->getType() == CC->ConstInt->getType()) {

      APInt Diff = CC->ConstInt->getValue() - MinValItr->ConstInt->getValue();
      if ((Diff.getBitWidth() <= 64) &&
          TTI->isLegalAddImmediate(Diff.getSExtValue()))
        continue;
    }


    findAndMakeBaseConstant(MinValItr, CC);

    MinValItr = CC;
  }

  findAndMakeBaseConstant(MinValItr, ConstCandVec.end());
}
