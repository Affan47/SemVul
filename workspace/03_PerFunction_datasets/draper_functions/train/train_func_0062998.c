InitMCObjectFileInfo(StringRef TT, Reloc::Model relocm,
                                            CodeModel::Model cm,
                                            MCContext &ctx) {
  RelocM = relocm;
  CMModel = cm;
  Ctx = &ctx;


  CommDirectiveSupportsAlignment = true;
  SupportsWeakOmittedEHFrame = true;
  IsFunctionEHFrameSymbolPrivate = true;

  PersonalityEncoding = LSDAEncoding = FDEEncoding = FDECFIEncoding =
    TTypeEncoding = dwarf::DW_EH_PE_absptr;

  EHFrameSection = 0;
  CompactUnwindSection = 0;

  Triple T(TT);
  Triple::ArchType Arch = T.getArch();


  if ((Arch == Triple::x86 || Arch == Triple::x86_64 ||
       Arch == Triple::arm || Arch == Triple::thumb ||
       Arch == Triple::ppc || Arch == Triple::ppc64 ||
       Arch == Triple::UnknownArch) &&
      (T.isOSDarwin() || T.getEnvironment() == Triple::MachO)) {
    Env = IsMachO;
    InitMachOMCObjectFileInfo(T);
  } else if ((Arch == Triple::x86 || Arch == Triple::x86_64) &&
             (T.getOS() == Triple::MinGW32 || T.getOS() == Triple::Cygwin ||
              T.getOS() == Triple::Win32)) {
    Env = IsCOFF;
    InitCOFFMCObjectFileInfo(T);
  } else {
    Env = IsELF;
    InitELFMCObjectFileInfo(T);
  }
}
