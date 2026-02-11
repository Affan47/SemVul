bmp_pad(FILE *f) {
  int c, i, b;

  c = (-bmp_count) & 3;
  for (i=0; i<c; i++) {
    b = fgetc(f);
    if (b==EOF) {
      return 1;
    }
  }
  bmp_pos += c;
  bmp_count = 0;
  return 0;
}
