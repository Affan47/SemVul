pushFrame(const Insn *next, int argsPushed)
{
  if (csp >= cslim) {
    size_t newSize = csbase ? (cslim - csbase)*2 : 8;
    ControlStackEntry *newBase = new ControlStackEntry[newSize];
    cslim = newBase + newSize;
    ControlStackEntry *newP = newBase;
    for (const ControlStackEntry *oldP = csbase; oldP < csp; oldP++)
      *newP++ = *oldP;
    csp = newP;
    if (csbase)
      delete [] csbase;
    csbase = newBase;
  }
  csp->closure = closure;
  csp->protectClosure = protectClosure;
  csp->next = next;
  csp->frameSize = sp - frame - argsPushed;
  csp->closureLoc = closureLoc;
  csp->continuation = 0;
  csp++;
}
