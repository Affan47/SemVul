parseCommand(bool &IsData, std::string &ModuleName,
                         uint64_t &ModuleOffset) {
  const char *kDataCmd = "DATA ";
  const char *kCodeCmd = "CODE ";
  const int kMaxInputStringLength = 1024;
  const char kDelimiters[] = " \n";
  char InputString[kMaxInputStringLength];
  if (!fgets(InputString, sizeof(InputString), stdin))
    return false;
  IsData = false;
  ModuleName = "";
  char *pos = InputString;
  if (strncmp(pos, kDataCmd, strlen(kDataCmd)) == 0) {
    IsData = true;
    pos += strlen(kDataCmd);
  } else if (strncmp(pos, kCodeCmd, strlen(kCodeCmd)) == 0) {
    IsData = false;
    pos += strlen(kCodeCmd);
  } else {

    IsData = false;
  }

  if (ClBinaryName == "") {
    pos += strspn(pos, kDelimiters);
    if (*pos == '"' || *pos == '\'') {
      char quote = *pos;
      pos++;
      char *end = strchr(pos, quote);
      if (!end)
        return false;
      ModuleName = std::string(pos, end - pos);
      pos = end + 1;
    } else {
      int name_length = strcspn(pos, kDelimiters);
      ModuleName = std::string(pos, name_length);
      pos += name_length;
    }
  } else {
    ModuleName = ClBinaryName;
  }

  pos += strspn(pos, kDelimiters);
  int offset_length = strcspn(pos, kDelimiters);
  return !StringRef(pos, offset_length).getAsInteger(0, ModuleOffset);
}
