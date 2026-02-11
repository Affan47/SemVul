getValueStr(const Option &O, const char *DefaultMsg) {
  if (O.ValueStr[0] == 0) return DefaultMsg;
  return O.ValueStr;
}
