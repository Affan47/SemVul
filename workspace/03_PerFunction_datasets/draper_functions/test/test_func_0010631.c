LLVMInitializeAArch64TargetMC() {
  for (Target *T :
       {&TheAArch64leTarget, &TheAArch64beTarget, &TheARM64Target}) {

    RegisterMCAsmInfoFn X(*T, createAArch64MCAsmInfo);


    TargetRegistry::RegisterMCCodeGenInfo(*T, createAArch64MCCodeGenInfo);


    TargetRegistry::RegisterMCInstrInfo(*T, createAArch64MCInstrInfo);


    TargetRegistry::RegisterMCRegInfo(*T, createAArch64MCRegisterInfo);


    TargetRegistry::RegisterMCSubtargetInfo(*T, createAArch64MCSubtargetInfo);


    TargetRegistry::RegisterMCCodeEmitter(*T, createAArch64MCCodeEmitter);


    TargetRegistry::RegisterELFStreamer(*T, createELFStreamer);
    TargetRegistry::RegisterMachOStreamer(*T, createMachOStreamer);


    TargetRegistry::RegisterObjectTargetStreamer(
        *T, createAArch64ObjectTargetStreamer);


    TargetRegistry::RegisterAsmTargetStreamer(*T,
                                              createAArch64AsmTargetStreamer);

    TargetRegistry::RegisterMCInstPrinter(*T, createAArch64MCInstPrinter);
  }


  for (Target *T : {&TheAArch64leTarget, &TheARM64Target})
    TargetRegistry::RegisterMCAsmBackend(*T, createAArch64leAsmBackend);
  TargetRegistry::RegisterMCAsmBackend(TheAArch64beTarget,
                                       createAArch64beAsmBackend);
}
