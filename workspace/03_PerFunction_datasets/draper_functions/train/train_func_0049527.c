make(int n, InsnPtr next)
{
  if (!next.isNull()) {
    int i;
    if (next->isReturn(i))
      return new ReturnInsn(n + i);
    if (next->isPopBindings(i, next))
      return new PopBindingsInsn(n + i, next);
  }
  return new PopBindingsInsn(n, next);
}
