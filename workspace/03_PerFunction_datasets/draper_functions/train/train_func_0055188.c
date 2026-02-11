copy(int n) {
  int i;

  if (sp + n > psStackSize) {
    error(-1, "Stack underflow in PostScript function");
    return;
  }
  if (!checkOverflow(n)) {
    return;
  }
  for (i = sp + n - 1; i >= sp; --i) {
    stack[i - n] = stack[i];
  }
  sp -= n;
}
