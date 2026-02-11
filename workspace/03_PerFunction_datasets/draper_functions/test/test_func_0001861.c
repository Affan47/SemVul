ParseHead(const StringRef &Input, StringRef &FName,
                      uint64_t &NumSamples, uint64_t &NumHeadSamples) {
  if (Input[0] == ' ')
    return false;
  size_t n2 = Input.rfind(':');
  size_t n1 = Input.rfind(':', n2 - 1);
  FName = Input.substr(0, n1);
  if (Input.substr(n1 + 1, n2 - n1 - 1).getAsInteger(10, NumSamples))
    return false;
  if (Input.substr(n2 + 1).getAsInteger(10, NumHeadSamples))
    return false;
  return true;
}
