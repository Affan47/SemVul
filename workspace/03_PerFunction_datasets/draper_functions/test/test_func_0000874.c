indentAfterNewLine(StringRef Str,
                                      std::string &NewStr,
                                      const std::string &IndentStr)
{
  SmallVector<StringRef, 20> StrVec;
  Str.split(StrVec, "\n");
  NewStr = "";
  for(SmallVector<StringRef, 20>::iterator I = StrVec.begin(),
      E = StrVec.end(); I != E; ++I) {
    NewStr += ((*I).str() + "\n" + IndentStr);
  }
}
