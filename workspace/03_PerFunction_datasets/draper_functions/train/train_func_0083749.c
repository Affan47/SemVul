importedSymbolEnd(uint32_t RVA, const COFFObjectFile *Object) {
  uintptr_t IntPtr = 0;
  Object->getRvaPtr(RVA, IntPtr);

  int Index = 0;
  if (Object->getBytesInAddress() == 4) {
    auto *Entry = reinterpret_cast<ulittle32_t *>(IntPtr);
    while (*Entry++)
      ++Index;
  } else {
    auto *Entry = reinterpret_cast<ulittle64_t *>(IntPtr);
    while (*Entry++)
      ++Index;
  }
  return makeImportedSymbolIterator(Object, IntPtr, Index);
}
