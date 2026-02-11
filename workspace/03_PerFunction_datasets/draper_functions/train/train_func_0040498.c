dump(const PDBSymbolTypeUDT &Symbol) {
  if (Symbol.getUnmodifiedTypeId() != 0)
    return;
  if (Printer.IsTypeExcluded(Symbol.getName()))
    return;

  Printer.NewLine();

  if (opts::NoClassDefs) {
    WithColor(Printer, PDB_ColorItem::Keyword).get() << "class ";
    WithColor(Printer, PDB_ColorItem::Identifier).get() << Symbol.getName();
  } else {
    ClassDefinitionDumper Dumper(Printer);
    Dumper.start(Symbol);
  }
}
