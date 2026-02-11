print(raw_ostream &OS, const Module *M,
                     bool ) const {
  ModuleSlotTracker MST(M, isa<MDNode>(this));
  printMetadataImpl(OS, *this, MST, M,  false);
}
