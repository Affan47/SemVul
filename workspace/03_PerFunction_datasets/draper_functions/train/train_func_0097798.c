elideCopiesAndPHIs(MachineInstr *MI,
                                        SmallVectorImpl<MachineInstr*> &Outs) {


   std::set<MachineInstr *> Reached;
   SmallVector<MachineInstr *, 8> Front;
   Front.push_back(MI);
   while (Front.size() != 0) {
     MI = Front.back();
     Front.pop_back();


     if (Reached.find(MI) != Reached.end())
       continue;
     Reached.insert(MI);
     if (MI->isPHI()) {
       for (unsigned I = 1, E = MI->getNumOperands(); I != E; I += 2) {
         unsigned Reg = MI->getOperand(I).getReg();
         if (!TRI->isVirtualRegister(Reg)) {
           continue;
         }
         MachineInstr *NewMI = MRI->getVRegDef(Reg);
         if (!NewMI)
           continue;
         Front.push_back(NewMI);
       }
     } else if (MI->isFullCopy()) {
       if (!TRI->isVirtualRegister(MI->getOperand(1).getReg()))
         continue;
       MachineInstr *NewMI = MRI->getVRegDef(MI->getOperand(1).getReg());
       if (!NewMI)
         continue;
       Front.push_back(NewMI);
     } else {
       DEBUG(dbgs() << "Found partial copy" << *MI <<"\n");
       Outs.push_back(MI);
     }
   }
}
