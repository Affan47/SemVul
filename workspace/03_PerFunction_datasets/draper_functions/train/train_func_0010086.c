renderLineNumberColumn(raw_ostream &OS,
                                                unsigned LineNo) {
  SmallString<32> Buffer;
  raw_svector_ostream BufferOS(Buffer);
  BufferOS << LineNo;
  auto Str = BufferOS.str();

  Str = Str.substr(0, std::min(Str.size(), (size_t)LineNumberColumnWidth));
  OS.indent(LineNumberColumnWidth - Str.size()) << Str << '|';
}
