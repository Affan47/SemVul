CreateNeg(Value *S1, const Twine &Name,
                                 Instruction *InsertBefore, Value *FlagsOp) {
  if (S1->getType()->isIntOrIntVectorTy())
    return BinaryOperator::CreateNeg(S1, Name, InsertBefore);
  else {
    BinaryOperator *Res = BinaryOperator::CreateFNeg(S1, Name, InsertBefore);
    Res->setFastMathFlags(cast<FPMathOperator>(FlagsOp)->getFastMathFlags());
    return Res;
  }
}
