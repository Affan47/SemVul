tab(void)
{
  if (sensitive()==MSTrue&&isProtected()==MSFalse) insertString(MSTextTabString);
  else top()->traverseToNext();
}
