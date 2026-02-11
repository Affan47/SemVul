isCString() const {
  if (!isString())
    return false;

  StringRef Str = getAsString();


  if (Str.back() != 0) return false;


  return Str.drop_back().find(0) == StringRef::npos;
}
