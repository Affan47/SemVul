getArcLength(const char *line) {
  const char *pos;

  if ((pos = getArcField(line, 9)) != NULL
      || (pos = getArcField(line, 4)) != NULL
      || (pos = getArcField(line, 2)) != NULL) {
    int length;

    if (sscanf(pos, "%d", &length) == 1) {
      return length;
    }
  }
  return -1;
}
