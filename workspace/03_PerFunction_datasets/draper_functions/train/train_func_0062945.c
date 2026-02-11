createObjectWriter(raw_ostream &OS) const {
      bool is64 = getPointerSize() == 8;
      return createMachObjectWriter(new PPCMachObjectWriter(
                                      is64,
                                      (is64 ? object::mach::CTM_PowerPC64 :
                                       object::mach::CTM_PowerPC),
                                      object::mach::CSPPC_ALL),
                                    OS, false);
    }
