WriteChars(const char* filename,
               const char* str,
               int size,
               bool verbose) {
  FILE* f = OS::FOpen(filename, "wb");
  if (f == NULL) {
    if (verbose) {
      OS::PrintError("Cannot open file %s for writing.\n", filename);
    }
    return 0;
  }
  int written = WriteCharsToFile(str, size, f);
  fclose(f);
  return written;
}
