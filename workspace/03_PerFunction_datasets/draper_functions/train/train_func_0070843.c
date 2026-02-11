split(const std::string& source, char delimiter,
             std::vector<std::string>* fields) {
  ASSERT(NULL != fields);
  fields->clear();
  size_t last = 0;
  for (size_t i = 0; i < source.length(); ++i) {
    if (source[i] == delimiter) {
      fields->push_back(source.substr(last, i - last));
      last = i + 1;
    }
  }
  fields->push_back(source.substr(last, source.length() - last));
  return fields->size();
}
