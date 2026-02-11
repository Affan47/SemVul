FileCopy(const std::string& source_path,int destination_handle) {
  int source_handle = ::open(source_path.c_str(),O_RDONLY,0);
  if(source_handle == -1) return false;
  if(::ftruncate(destination_handle,0) != 0) {
    ::close(source_handle);
    return false;
  }
  bool r = FileCopy(source_handle,destination_handle);
  ::close(source_handle);
  return r;
}
