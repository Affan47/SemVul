setFontFamilyName(const StringC &name)
{
  const int *p = fontFamilyNameTable_.lookup(name);
  if (!p) {
    specFormat_.fontFamily = fontFamilyCharsetsTable_.size();
    fontFamilyNameTable_.insert(name, specFormat_.fontFamily);
    fontFamilyCharsetsTable_.resize(fontFamilyCharsetsTable_.size() + 1);
  }
  else
    specFormat_.fontFamily = *p;
}
