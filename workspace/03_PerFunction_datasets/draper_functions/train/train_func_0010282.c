hasInlineAsmMemConstraint(std::vector<InlineAsm::ConstraintInfo> &CInfos,
                                const TargetLowering &TLI) {
  for (unsigned i = 0, e = CInfos.size(); i != e; ++i) {
    InlineAsm::ConstraintInfo &CI = CInfos[i];
    for (unsigned j = 0, ee = CI.Codes.size(); j != ee; ++j) {
      TargetLowering::ConstraintType CType = TLI.getConstraintType(CI.Codes[j]);
      if (CType == TargetLowering::C_Memory)
        return true;
    }


    if (CI.isIndirect)
      return true;
  }

  return false;
}
