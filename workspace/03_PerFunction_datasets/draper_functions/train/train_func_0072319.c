print(raw_ostream &OS, const Module *M) const {
  OS << "Types in use by this module:\n";
  for (SetVector<Type *>::const_iterator I = UsedTypes.begin(),
       E = UsedTypes.end(); I != E; ++I) {
    OS << "   " << **I << '\n';
  }
}
