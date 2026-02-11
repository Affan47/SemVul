getRegForInlineAsmConstraint(
    const TargetRegisterInfo *TRI, StringRef Constraint, MVT VT) const {
  if (Constraint.size() == 1) {

    switch (Constraint[0]) {
    default: break;
    case 'd':
    case 'r':
      if (VT == MVT::i64)
        return std::make_pair(0U, &SystemZ::GR64BitRegClass);
      else if (VT == MVT::i128)
        return std::make_pair(0U, &SystemZ::GR128BitRegClass);
      return std::make_pair(0U, &SystemZ::GR32BitRegClass);

    case 'a':
      if (VT == MVT::i64)
        return std::make_pair(0U, &SystemZ::ADDR64BitRegClass);
      else if (VT == MVT::i128)
        return std::make_pair(0U, &SystemZ::ADDR128BitRegClass);
      return std::make_pair(0U, &SystemZ::ADDR32BitRegClass);

    case 'h':
      return std::make_pair(0U, &SystemZ::GRH32BitRegClass);

    case 'f':
      if (VT == MVT::f64)
        return std::make_pair(0U, &SystemZ::FP64BitRegClass);
      else if (VT == MVT::f128)
        return std::make_pair(0U, &SystemZ::FP128BitRegClass);
      return std::make_pair(0U, &SystemZ::FP32BitRegClass);
    }
  }
  if (Constraint.size() > 0 && Constraint[0] == '{') {


    if (Constraint[1] == 'r') {
      if (VT == MVT::i32)
        return parseRegisterNumber(Constraint, &SystemZ::GR32BitRegClass,
                                   SystemZMC::GR32Regs);
      if (VT == MVT::i128)
        return parseRegisterNumber(Constraint, &SystemZ::GR128BitRegClass,
                                   SystemZMC::GR128Regs);
      return parseRegisterNumber(Constraint, &SystemZ::GR64BitRegClass,
                                 SystemZMC::GR64Regs);
    }
    if (Constraint[1] == 'f') {
      if (VT == MVT::f32)
        return parseRegisterNumber(Constraint, &SystemZ::FP32BitRegClass,
                                   SystemZMC::FP32Regs);
      if (VT == MVT::f128)
        return parseRegisterNumber(Constraint, &SystemZ::FP128BitRegClass,
                                   SystemZMC::FP128Regs);
      return parseRegisterNumber(Constraint, &SystemZ::FP64BitRegClass,
                                 SystemZMC::FP64Regs);
    }
  }
  return TargetLowering::getRegForInlineAsmConstraint(TRI, Constraint, VT);
}
