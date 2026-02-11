url() const {
  std::string s = "file:///";
  for (size_t i=0; i<folder_.length(); ++i) {
    if (IsFolderDelimiter(folder_[i]))
      s += '/';
    else
      s += folder_[i];
  }
  s += basename_;
  s += extension_;
  return UrlEncodeStringForOnlyUnsafeChars(s);
}
