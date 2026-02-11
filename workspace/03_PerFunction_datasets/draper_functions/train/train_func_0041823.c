Lookup(ArrayRef<TableEntry> Table, unsigned Opcode) {
  const TableEntry *I = std::lower_bound(Table.begin(), Table.end(), Opcode);
  if (I != Table.end() && I->from == Opcode)
    return I->to;
  return -1;
}
