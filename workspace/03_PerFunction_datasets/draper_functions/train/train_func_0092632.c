getPunktPos(Str na) {
  for (int i = 0; i < (int) na.length(); i++)
    if (na[i] == '.') return i;
  return -1;
}
