getRecords(
    StringRef FuncName, ArrayRef<InstrProfRecord> &Data) {
  auto Iter = Index->find(FuncName);
  if (Iter == Index->end()) return instrprof_error::unknown_function;

  Data = (*Iter);
  if (Data.empty()) return instrprof_error::malformed;

  return instrprof_error::success;
}
