ReadPnm(const char *filename, ByteImage *im) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    LOG(ERROR) << "Error: Couldn't open " << filename << " fopen returned 0";
    return 0;
  }
  int res = ReadPnmStream(file, im);
  fclose(file);
  return res;
}
