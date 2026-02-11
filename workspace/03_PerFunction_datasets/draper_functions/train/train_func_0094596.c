FormatFileLocation(const char* file, int line) {
  const char* const file_name = file == NULL ? kUnknownFile : file;

  if (line < 0) {
    return String::Format("%s:", file_name).c_str();
  }
#ifdef _MSC_VER
  return String::Format("%s(%d):", file_name, line).c_str();
#else
  return String::Format("%s:%d:", file_name, line).c_str();
#endif
}
