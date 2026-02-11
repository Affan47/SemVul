writeOperandInternal(Value *Operand, bool Static) {
  if (Instruction *I = dyn_cast<Instruction>(Operand))

    if (isInlinableInst(*I) && !isDirectAlloca(I)) {
      Out << '(';
      writeInstComputationInline(*I);
      Out << ')';
      return;
    }

  Constant* CPV = dyn_cast<Constant>(Operand);

  if (CPV && !isa<GlobalValue>(CPV))
    printConstant(CPV, Static);
  else
    Out << GetValueName(Operand);
}
