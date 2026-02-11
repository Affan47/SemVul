Open(const std::string& filename) {
  FileStream* fs = new FileStream();
  if (!fs->Open(filename, "r", NULL)) {
    return false;
  }
  instream_.reset(fs);
  return true;
}
