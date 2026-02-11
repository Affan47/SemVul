getBlockNum(MachineBasicBlock *BB) {
  std::string Result;
  raw_string_ostream OS(Result);
  OS << "BB#" << BB->getNumber();
  OS.flush();
  return Result;
}
