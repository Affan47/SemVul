getUniqueSourceFiles() const {
  std::vector<StringRef> Filenames;
  for (const auto &Function : getCoveredFunctions())
    Filenames.insert(Filenames.end(), Function.Filenames.begin(),
                     Function.Filenames.end());
  std::sort(Filenames.begin(), Filenames.end());
  auto Last = std::unique(Filenames.begin(), Filenames.end());
  Filenames.erase(Last, Filenames.end());
  return Filenames;
}
