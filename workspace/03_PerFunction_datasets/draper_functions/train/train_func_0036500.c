CallVABD(CallInst *CI, Value *Arg0, Value *Arg1) {
  Function *F = CI->getCalledFunction();
  const std::string& Name = F->getName();
  bool isLong = (Name.at(18) == 'l');
  bool isSigned = (Name.at(isLong ? 19 : 18) == 's');

  Intrinsic::ID intID;
  if (isSigned)
    intID = Intrinsic::arm_neon_vabds;
  else
    intID = Intrinsic::arm_neon_vabdu;

  const Type *Ty = CI->getType();
  if (isLong)
    Ty = VectorType::getTruncatedElementVectorType(cast<const VectorType>(Ty));

  Function *VABD = Intrinsic::getDeclaration(F->getParent(), intID, &Ty, 1);
  Value *Operands[2];
  Operands[0] = Arg0;
  Operands[1] = Arg1;
  return CallInst::Create(VABD, Operands, Operands+2,
                          "upgraded."+CI->getName(), CI);
}
