addLineCount(StringRef Filename, uint32_t Line, uint32_t Count) {
  if (LineInfo.find(Filename) == LineInfo.end()) {
    OwningPtr<MemoryBuffer> Buff;
    if (error_code ec = MemoryBuffer::getFileOrSTDIN(Filename, Buff)) {
      errs() << Filename << ": " << ec.message() << "\n";
      return;
    }
    StringRef AllLines = Buff.take()->getBuffer();
    LineCounts L(AllLines.count('\n')+2);
    L[Line-1] = Count;
    LineInfo[Filename] = L;
    return;
  }
  LineCounts &L = LineInfo[Filename];
  L[Line-1] = Count;
}
