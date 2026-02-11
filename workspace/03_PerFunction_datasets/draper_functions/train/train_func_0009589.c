EmitLinkage(unsigned Linkage, MCSymbol *GVSym) const {
  switch ((GlobalValue::LinkageTypes)Linkage) {
  case GlobalValue::CommonLinkage:
  case GlobalValue::LinkOnceAnyLinkage:
  case GlobalValue::LinkOnceODRLinkage:
  case GlobalValue::WeakAnyLinkage:
  case GlobalValue::WeakODRLinkage:
  case GlobalValue::LinkerPrivateWeakLinkage:
  case GlobalValue::LinkerPrivateWeakDefAutoLinkage:
    if (MAI->getWeakDefDirective() != 0) {

      OutStreamer.EmitSymbolAttribute(GVSym, MCSA_Global);

      if ((GlobalValue::LinkageTypes)Linkage !=
          GlobalValue::LinkerPrivateWeakDefAutoLinkage)

        OutStreamer.EmitSymbolAttribute(GVSym, MCSA_WeakDefinition);
      else
        OutStreamer.EmitSymbolAttribute(GVSym, MCSA_WeakDefAutoPrivate);
    } else if (MAI->getLinkOnceDirective() != 0) {

      OutStreamer.EmitSymbolAttribute(GVSym, MCSA_Global);

    } else {

      OutStreamer.EmitSymbolAttribute(GVSym, MCSA_Weak);
    }
    break;
  case GlobalValue::DLLExportLinkage:
  case GlobalValue::AppendingLinkage:


  case GlobalValue::ExternalLinkage:


    OutStreamer.EmitSymbolAttribute(GVSym, MCSA_Global);
    break;
  case GlobalValue::PrivateLinkage:
  case GlobalValue::InternalLinkage:
  case GlobalValue::LinkerPrivateLinkage:
    break;
  default:
    llvm_unreachable("Unknown linkage type!");
  }
}
