AppendPathname(const std::string& pathname) {
  std::string full_pathname(folder_);
  full_pathname.append(pathname);
  SetPathname(full_pathname);
}
