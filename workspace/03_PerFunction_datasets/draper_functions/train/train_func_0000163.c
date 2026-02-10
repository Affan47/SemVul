allocateCandidatesAndFindBasisForAdd(
    Value *LHS, Value *RHS, Instruction *I) {
  Value *S = nullptr;
  ConstantInt *Idx = nullptr;
  if (match(RHS, m_Mul(m_Value(S), m_ConstantInt(Idx)))) {

    allocateCandidatesAndFindBasis(Candidate::Add, SE->getSCEV(LHS), Idx, S, I);
  } else if (match(RHS, m_Shl(m_Value(S), m_ConstantInt(Idx)))) {

    APInt One(Idx->getBitWidth(), 1);
    Idx = ConstantInt::get(Idx->getContext(), One << Idx->getValue());
    allocateCandidatesAndFindBasis(Candidate::Add, SE->getSCEV(LHS), Idx, S, I);
  } else {

    ConstantInt *One = ConstantInt::get(cast<IntegerType>(I->getType()), 1);
    allocateCandidatesAndFindBasis(Candidate::Add, SE->getSCEV(LHS), One, RHS,
                                   I);
  }
}
