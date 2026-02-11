HasResourceStream(const std::string& id, size_t index) const {
  const Entry* entry = GetEntry(id);
  if ((NULL == entry) || (index >= entry->streams))
    return false;

  std::string filename = IdToFilename(id, index);

  return FileExists(filename);
}
