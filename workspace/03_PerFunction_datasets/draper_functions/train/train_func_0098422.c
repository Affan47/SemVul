visitInsertElementInst(InsertElementInst &I) {
  Type *EltTy = I.getType()->getElementType();
  writeOperand(I.getOperand(0));
  Out << ";\n  ";
  Out << "((";
  printType(Out, PointerType::getUnqual(EltTy));
  Out << ")(&" << GetValueName(&I) << "))[";
  writeOperand(I.getOperand(2));
  Out << "] = (";
  writeOperand(I.getOperand(1));
  Out << ")";
}
