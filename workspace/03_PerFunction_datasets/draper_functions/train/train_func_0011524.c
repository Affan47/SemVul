pop_stack(void)
{
  long n;
  if (sp==0) {
    writeln("GAME ERROR: Stack underflow.");
    return 0;
  }
  n=stack[--sp];
  if (sp+100<stacksize) {
    stacksize-=50;
    stack=rrealloc(stack,stacksize*sizeof(long));
  }
  return n;
}
