getRegClassForRegister(Record *R) {
  const CodeGenRegister *Reg = getReg(R);
  ArrayRef<CodeGenRegisterClass*> RCs = getRegClasses();
  const CodeGenRegisterClass *FoundRC = 0;
  for (unsigned i = 0, e = RCs.size(); i != e; ++i) {
    const CodeGenRegisterClass &RC = *RCs[i];
    if (!RC.contains(Reg))
      continue;


    if (!FoundRC) {
      FoundRC = &RC;
      continue;
    }


    if (RC.getValueTypes() != FoundRC->getValueTypes())
      return 0;


    if (RC.hasSubClass(FoundRC)) {
      FoundRC = &RC;
      continue;
    }


    if (FoundRC->hasSubClass(&RC))
      continue;


    return 0;
  }
  return FoundRC;
}
