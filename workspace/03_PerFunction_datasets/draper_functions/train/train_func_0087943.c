getRegForInlineAsmConstraint(const std::string &Constraint,
                                                  EVT VT) const {
  if (Constraint.size() == 1) {
    switch (Constraint[0]) {
    case 'r':
      return std::make_pair(0U, SP::IntRegsRegisterClass);
    }
  }

  return TargetLowering::getRegForInlineAsmConstraint(Constraint, VT);
}
