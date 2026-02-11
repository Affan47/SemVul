SetPermissions(const char* file, mode_t mode,
                                 bool honor_umask)
{
  if (!file) {
    return false;
  }
  return SystemTools::SetPermissions(std::string(file), mode, honor_umask);
}
