lookup(unsigned opcode, unsigned domain) {
  for (unsigned i = 0, e = array_lengthof(ReplaceableInstrs); i != e; ++i)
    if (ReplaceableInstrs[i][domain-1] == opcode)
      return ReplaceableInstrs[i];
  return 0;
}
