dump(raw_ostream &OS) const {
  OS << format("0x%16.16llx %6u %6u", Address, Line, Column)
     << format(" %6u %3u ", File, Isa)
     << (IsStmt ? " is_stmt" : "")
     << (BasicBlock ? " basic_block" : "")
     << (PrologueEnd ? " prologue_end" : "")
     << (EpilogueBegin ? " epilogue_begin" : "")
     << (EndSequence ? " end_sequence" : "")
     << '\n';
}
