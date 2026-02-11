insertfile(const char *file, int pos, int buflen) {
  FILE *fp;  int r;
  if (!(fp = fopen(file, "r"))) return 1;
  char *buffer = new char[buflen];
  for (; (r = fread(buffer, 1, buflen - 1, fp)) > 0; pos += r) {
    buffer[r] = (char)0;
    insert(pos, buffer);
  }

  int e = ferror(fp) ? 2 : 0;
  fclose(fp);
  delete[] buffer;
  return e;
}
