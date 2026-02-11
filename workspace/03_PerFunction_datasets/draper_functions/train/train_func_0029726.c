compareAddress(const SymEntry *A, const SymEntry *B) {
  if (A->SectionID != B->SectionID)
    return A->SectionID - B->SectionID;
  return A->Address - B->Address;
}
