getUniqueName(StringRef BaseName) const {
  std::string TryName = BaseName;

  const_iterator End = tmap.end();


  while (tmap.find(TryName) != End)
    TryName = BaseName.str() + utostr(++LastUnique);
  return TryName;
}
