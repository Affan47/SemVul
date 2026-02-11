EmitVisibility(MCSymbol *Sym, unsigned Visibility,
                                bool IsDefinition) const {
  MCSymbolAttr Attr = MCSA_Invalid;

  switch (Visibility) {
  default: break;
  case GlobalValue::HiddenVisibility:
    if (IsDefinition)
      Attr = MAI->getHiddenVisibilityAttr();
    else
      Attr = MAI->getHiddenDeclarationVisibilityAttr();
    break;
  case GlobalValue::ProtectedVisibility:
    Attr = MAI->getProtectedVisibilityAttr();
    break;
  }

  if (Attr != MCSA_Invalid)
    OutStreamer->EmitSymbolAttribute(Sym, Attr);
}
