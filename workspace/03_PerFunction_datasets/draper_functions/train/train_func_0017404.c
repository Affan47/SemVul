printInst(const MCInst *MI, raw_ostream &OS,
                                    StringRef Annot,
                                    const MCSubtargetInfo &STI) {
  const MCInstrDesc &Desc = MII.get(MI->getOpcode());
  uint64_t TSFlags = Desc.TSFlags;

  if (TSFlags & X86II::LOCK)
    OS << "\tlock\n";

  printInstruction(MI, OS);


  printAnnotation(OS, Annot);


  if (CommentStream)
    EmitAnyX86InstComments(MI, *CommentStream, getRegisterName);
}
