print(const boundaryType &p) {
  static char buf[4];
  if(p.isValid()) {
	buf[0] = '1';
  } else {
	buf[0] = '0';
  }
  buf[1] = '\0';

  return buf;
}
