parent_folder() const {
  std::string::size_type pos = std::string::npos;
  if (folder_.size() >= 2) {
    pos = folder_.find_last_of(FOLDER_DELIMS, folder_.length() - 2);
  }
  if (pos != std::string::npos) {
    return folder_.substr(0, pos + 1);
  } else {
    return EMPTY_STR;
  }
}
