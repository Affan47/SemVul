unload(const std::string& path) {
  std::lock_guard<std::mutex> lock(guard);
  auto it = libs.find(path);
  if (libs.end() != it) {
    it->second.reset();
    libs.erase(it);
  }
}
