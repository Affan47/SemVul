last_name(void) {
  int pl=point.rfind('/');
  if(pl == -1) return point;
  return point.substr(pl+1);
}
