closePhysRegsUsed(const TargetRegisterInfo &TRI) {
  for (int i = UsedPhysRegs.find_first(); i >= 0;
       i = UsedPhysRegs.find_next(i))
         for (const unsigned *SS = TRI.getSubRegisters(i);
              unsigned SubReg = *SS; ++SS)
           if (SubReg > unsigned(i))
             UsedPhysRegs.set(SubReg);
}
