GetAutoSenseRadix(StringRef &Str) {
  if (Str.startswith("0x")) {
    Str = Str.substr(2);
    return 16;
  }

  if (Str.startswith("0b")) {
    Str = Str.substr(2);
    return 2;
  }

  if (Str.startswith("0o")) {
    Str = Str.substr(2);
    return 8;
  }

  if (Str.startswith("0"))
    return 8;

  return 10;
}
