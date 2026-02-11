runOnInstruction(MachineInstr *MI) {


  SmallVector<unsigned, 8> Defs = getReadDPRs(MI);
  bool Modified = false;

  for (SmallVectorImpl<unsigned>::iterator I = Defs.begin(), E = Defs.end();
     I != E; ++I) {


    SmallVector<MachineInstr *, 8> DefSrcs;
    if (!TRI->isVirtualRegister(*I))
      continue;
    MachineInstr *Def = MRI->getVRegDef(*I);
    if (!Def)
      continue;

    elideCopiesAndPHIs(Def, DefSrcs);

    for (SmallVectorImpl<MachineInstr *>::iterator II = DefSrcs.begin(),
      EE = DefSrcs.end(); II != EE; ++II) {
      MachineInstr *MI = *II;


      if (Replacements.find(MI) != Replacements.end())
        continue;


      if (!hasPartialWrite(MI))
        continue;


      SmallVector<MachineOperand*, 8> Uses;
      unsigned DPRDefReg = MI->getOperand(0).getReg();
      for (MachineRegisterInfo::use_iterator I = MRI->use_begin(DPRDefReg),
             E = MRI->use_end(); I != E; ++I)
        Uses.push_back(&*I);


      unsigned NewReg = optimizeSDPattern(MI);

      if (NewReg != 0) {
        Modified = true;
        for (SmallVectorImpl<MachineOperand *>::const_iterator I = Uses.begin(),
               E = Uses.end(); I != E; ++I) {


          MRI->constrainRegClass(NewReg, MRI->getRegClass((*I)->getReg()));

          DEBUG(dbgs() << "Replacing operand "
                       << **I << " with "
                       << PrintReg(NewReg) << "\n");
          (*I)->substVirtReg(NewReg, 0, *TRI);
        }
      }
      Replacements[MI] = NewReg;
    }
  }
  return Modified;
}
