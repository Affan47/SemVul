CreateNeg(Value *Op, const Twine &Name,
                                          BasicBlock *InsertAtEnd) {
  Value *zero = ConstantFP::getZeroValueForNegation(Op->getType());
  return new BinaryOperator(Instruction::Sub,
                            zero, Op,
                            Op->getType(), Name, InsertAtEnd);
}
