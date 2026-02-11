index(int i)
  {
    if (!checkOverflow()) {
      return;
    }
    --sp;
    if (sp + i + 1 >= psStackSize) {
      error(errSyntaxError, -1, "Stack underflow in PostScript function");
      return;
    }
    stack[sp] = stack[sp + 1 + i];
  }
