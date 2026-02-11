populateInstruction(const CodeGenInstruction &CGI,
                                  TARGET_NAME_t TN) {
  const Record &Def = *CGI.TheDef;
  const StringRef Name = Def.getName();
  uint8_t Form = getByteField(Def, "Form");

  BitsInit &Bits = getBitsField(Def, "Inst");


  if (Bits.allInComplete()) return false;


  if (Def.getValueAsBit("isAsmParserOnly"))
    return false;

  if (TN == TARGET_ARM) {
    if (Form == ARM_FORMAT_PSEUDO)
      return false;
    if (thumbInstruction(Form))
      return false;


    if (Name == "TCRETURNdi" || Name == "TCRETURNdiND" ||
        Name == "TCRETURNri" || Name == "TCRETURNriND" ||
        Name == "TAILJMPd"  || Name == "TAILJMPdt" ||
        Name == "TAILJMPdND" || Name == "TAILJMPdNDt" ||
        Name == "TAILJMPr"  || Name == "TAILJMPrND" ||
        Name == "MOVr_TC")
      return false;


    if (Name == "ADR")
      return false;


    if (Name == "VEXTd16" || Name == "VEXTd32" || Name == "VEXTdf" ||
        Name == "VEXTq16" || Name == "VEXTq32" || Name == "VEXTqf")
      return false;
  } else if (TN == TARGET_THUMB) {
    if (!thumbInstruction(Form))
      return false;


    if (Name == "tBX_RET" || Name == "tBX_RET_vararg")
      return false;


    if (Name == "tADR")
      return false;


    if (Name == "t2ADR")
      return false;


    if (Name == "tADDrSP" || Name == "tADDspr" || Name == "tPICADD" ||
        Name == "t2SUBrSPs" || Name == "t2ADDrSPs")
      return false;


    if (Name == "tLDRpci")
      return false;


    if (Name == "t2LDRDpci")
      return false;


    if (Name == "t2LDMIA_RET" ||
        Name == "tMOVCCi" || Name == "tMOVCCr" ||
        Name == "tLDRcp" ||
        Name == "t2MOVCCi16")
      return false;
  }

  DEBUG({

      switch (TargetName) {
      case TARGET_ARM:
      case TARGET_THUMB:
        errs() << Name << " " << stringForARMFormat((ARMFormat)Form);
        break;
      }

      errs() << " ";


      dumpBits(errs(), Bits);

      errs() << '\n';


      for (unsigned i = 0, e = CGI.Operands.size(); i != e; ++i) {
        const CGIOperandList::OperandInfo &Info = CGI.Operands[i];
        const std::string &OperandName = Info.Name;
        const Record &OperandDef = *Info.Rec;

        errs() << "\t" << OperandName << " (" << OperandDef.getName() << ")\n";
      }
    });

  return true;
}
