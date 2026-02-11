Byte2Direct(int nArg) {
  return (nArg == '+' ? 0 : nArg == '.' || nArg == '=' ? 1 : nArg == '-' ? 2 : 3);
}
