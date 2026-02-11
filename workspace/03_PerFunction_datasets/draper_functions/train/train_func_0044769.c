WriteStringRecord(unsigned Code, StringRef Str,
                              unsigned AbbrevToUse, BitstreamWriter &Stream) {
  SmallVector<unsigned, 64> Vals;


  for (unsigned i = 0, e = Str.size(); i != e; ++i) {
    if (AbbrevToUse && !BitCodeAbbrevOp::isChar6(Str[i]))
      AbbrevToUse = 0;
    Vals.push_back(Str[i]);
  }


  Stream.EmitRecord(Code, Vals, AbbrevToUse);
}
