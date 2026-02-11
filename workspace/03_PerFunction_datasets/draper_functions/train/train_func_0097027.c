load(const std::string& path) {
  std::lock_guard<std::mutex> lock(guard);
  auto it = libs.find(path);
  if (libs.end() == it) {
    return it->second;
  }
  return (libs[path] = Library::loadFromFile(path));
}
