LLVMSetDisasmOptions(LLVMDisasmContextRef DCR, uint64_t Options){
  if (Options & LLVMDisassembler_Option_UseMarkup){
      LLVMDisasmContext *DC = (LLVMDisasmContext *)DCR;
      MCInstPrinter *IP = DC->getIP();
      IP->setUseMarkup(1);
      DC->addOptions(LLVMDisassembler_Option_UseMarkup);
      Options &= ~LLVMDisassembler_Option_UseMarkup;
  }
  if (Options & LLVMDisassembler_Option_PrintImmHex){
      LLVMDisasmContext *DC = (LLVMDisasmContext *)DCR;
      MCInstPrinter *IP = DC->getIP();
      IP->setPrintImmHex(1);
      DC->addOptions(LLVMDisassembler_Option_PrintImmHex);
      Options &= ~LLVMDisassembler_Option_PrintImmHex;
  }
  if (Options & LLVMDisassembler_Option_AsmPrinterVariant){
      LLVMDisasmContext *DC = (LLVMDisasmContext *)DCR;

      const MCAsmInfo *MAI = DC->getAsmInfo();
      const MCInstrInfo *MII = DC->getInstrInfo();
      const MCRegisterInfo *MRI = DC->getRegisterInfo();
      int AsmPrinterVariant = MAI->getAssemblerDialect();
      AsmPrinterVariant = AsmPrinterVariant == 0 ? 1 : 0;
      MCInstPrinter *IP = DC->getTarget()->createMCInstPrinter(
          Triple(DC->getTripleName()), AsmPrinterVariant, *MAI, *MII, *MRI);
      if (IP) {
        DC->setIP(IP);
        DC->addOptions(LLVMDisassembler_Option_AsmPrinterVariant);
        Options &= ~LLVMDisassembler_Option_AsmPrinterVariant;
      }
  }
  if (Options & LLVMDisassembler_Option_SetInstrComments) {
    LLVMDisasmContext *DC = (LLVMDisasmContext *)DCR;
    MCInstPrinter *IP = DC->getIP();
    IP->setCommentStream(DC->CommentStream);
    DC->addOptions(LLVMDisassembler_Option_SetInstrComments);
    Options &= ~LLVMDisassembler_Option_SetInstrComments;
  }
  if (Options & LLVMDisassembler_Option_PrintLatency) {
    LLVMDisasmContext *DC = (LLVMDisasmContext *)DCR;
    DC->addOptions(LLVMDisassembler_Option_PrintLatency);
    Options &= ~LLVMDisassembler_Option_PrintLatency;
  }
  return (Options == 0);
}
