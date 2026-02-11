getDebugAranges() {
  if (Aranges)
    return Aranges.get();

  DataExtractor arangesData(getARangeSection(), isLittleEndian(), 0);

  Aranges.reset(new DWARFDebugAranges());
  Aranges->extract(arangesData);
  if (Aranges->isEmpty())
    Aranges->generate(this);
  return Aranges.get();
}
