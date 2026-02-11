push_stack(long val)
{
  sp++;
  if (sp>stacksize) {
    stacksize+=10;
    stack=rrealloc(stack,stacksize*sizeof(long));
  }
  stack[sp-1]=val;
}
