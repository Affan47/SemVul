hasBasePointer(const MachineFunction &MF) const {
   const MachineFrameInfo *MFI = MF.getFrameInfo();

   if (!EnableBasePointer)
     return false;


   bool CantUseFP = needsStackRealignment(MF);
   return CantUseFP && CantUseSP(MFI);
}
