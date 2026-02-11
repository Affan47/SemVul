visitXor(BinaryOperator &I) {
  Assert1(!isa<UndefValue>(I.getOperand(0)) ||
          !isa<UndefValue>(I.getOperand(1)),
          "Undefined result: xor(undef, undef)", &I);
}
