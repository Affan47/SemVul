file_to_string(const std::string& filename, std::string* out) {
  FILE* f = fopen(filename.c_str(), "rb");
  if (f==0) return false;
  fseek(f, 0, SEEK_END);
  int size = ftell(f);
  fseek(f, 0, SEEK_SET);
  char* dat = (char*)malloc(size);
  int read = fread(dat, 1, size, f);
  out->assign(dat, size);
  delete [] dat;
  return read == size;
}
