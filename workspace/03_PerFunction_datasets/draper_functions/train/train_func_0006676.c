computeInferredRegisterClasses() {


  typedef std::map<Record*, CodeGenRegister::Set, LessRecord> SubReg2SetMap;


  for (unsigned rci = 0; rci != RegClasses.size(); ++rci) {
    CodeGenRegisterClass &RC = *RegClasses[rci];


    SubReg2SetMap SRSets;
    for (CodeGenRegister::Set::const_iterator RI = RC.getMembers().begin(),
         RE = RC.getMembers().end(); RI != RE; ++RI) {
      const CodeGenRegister::SubRegMap &SRM = (*RI)->getSubRegs();
      for (CodeGenRegister::SubRegMap::const_iterator I = SRM.begin(),
           E = SRM.end(); I != E; ++I)
        SRSets[I->first].insert(*RI);
    }


    for (unsigned sri = 0, sre = SubRegIndices.size(); sri != sre; ++sri) {
      Record *SubIdx = SubRegIndices[sri];
      SubReg2SetMap::const_iterator I = SRSets.find(SubIdx);

      if (I == SRSets.end())
        continue;

      if (I->second.size() == RC.getMembers().size()) {
        RC.setSubClassWithSubReg(SubIdx, &RC);
        continue;
      }


      CodeGenRegisterClass::Key K(&I->second, RC.SpillSize, RC.SpillAlignment);
      RCKeyMap::const_iterator FoundI = Key2RC.find(K);
      if (FoundI != Key2RC.end()) {
        RC.setSubClassWithSubReg(SubIdx, FoundI->second);
        continue;
      }


      CodeGenRegisterClass *NewRC =
        new CodeGenRegisterClass(RC.getName() + "_with_" +
                                 I->first->getName(), K);
      addToMaps(NewRC);
      RC.setSubClassWithSubReg(SubIdx, NewRC);
    }
  }
}
