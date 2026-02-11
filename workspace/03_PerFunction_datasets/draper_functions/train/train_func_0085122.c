getBSSSection() {
  const MCSectionELF *BSS = (const MCSectionELF *)TLOF.getBSSSection();
  return getSection(BSS->getSectionName(), BSS->getType(), BSS->getFlags(), 4);
}
