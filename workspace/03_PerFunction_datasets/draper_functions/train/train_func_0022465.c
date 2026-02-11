computeComposites() {
  for (unsigned i = 0, e = Registers.size(); i != e; ++i) {
    CodeGenRegister *Reg1 = Registers[i];
    const CodeGenRegister::SubRegMap &SRM1 = Reg1->getSubRegs();
    for (CodeGenRegister::SubRegMap::const_iterator i1 = SRM1.begin(),
         e1 = SRM1.end(); i1 != e1; ++i1) {
      Record *Idx1 = i1->first;
      CodeGenRegister *Reg2 = i1->second;

      if (Reg1 == Reg2)
        continue;
      const CodeGenRegister::SubRegMap &SRM2 = Reg2->getSubRegs();

      for (CodeGenRegister::SubRegMap::const_iterator i2 = SRM2.begin(),
           e2 = SRM2.end(); i2 != e2; ++i2) {
        std::pair<Record*, Record*> IdxPair(Idx1, i2->first);
        CodeGenRegister *Reg3 = i2->second;

        if (Reg2 == Reg3)
          continue;

        for (CodeGenRegister::SubRegMap::const_iterator i1d = SRM1.begin(),
             e1d = SRM1.end(); i1d != e1d; ++i1d) {
          if (i1d->second == Reg3) {
            std::pair<CompositeMap::iterator, bool> Ins =
              Composite.insert(std::make_pair(IdxPair, i1d->first));

            if (!Ins.second && Ins.first->second != i1d->first) {
              errs() << "Warning: SubRegIndex " << getQualifiedName(Idx1)
                     << " and " << getQualifiedName(IdxPair.second)
                     << " compose ambiguously as "
                     << getQualifiedName(Ins.first->second) << " or "
                     << getQualifiedName(i1d->first) << "\n";
            }
          }
        }
      }
    }
  }


  for (CompositeMap::iterator i = Composite.begin(), e = Composite.end();
       i != e;) {
    CompositeMap::iterator j = i;
    ++i;
    if (j->first.second == j->second)
      Composite.erase(j);
  }
}
