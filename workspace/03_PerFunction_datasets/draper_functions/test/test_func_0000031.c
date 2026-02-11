getSingleConstraintMatchWeight(AsmOperandInfo &info,
                               const char *constraint) const {
  ConstraintWeight weight = CW_Invalid;
  Value *CallOperandVal = info.CallOperandVal;


  if (!CallOperandVal)
    return CW_Default;


  switch (*constraint) {
  default:
    weight = TargetLowering::getSingleConstraintMatchWeight(info, constraint);
    break;
  case 'I':
    if (ConstantInt *C = dyn_cast<ConstantInt>(info.CallOperandVal)) {
      if (isInt<13>(C->getSExtValue()))
        weight = CW_Constant;
    }
    break;
  }
  return weight;
}
