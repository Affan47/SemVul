PrintLoadStoreResults(const char *Msg, bool P, const Value *V1,
                      const Value *V2, const Module *M) {
  if (P) {
    errs() << "  " << Msg << ": " << *V1
           << " <-> " << *V2 << '\n';
  }
}
