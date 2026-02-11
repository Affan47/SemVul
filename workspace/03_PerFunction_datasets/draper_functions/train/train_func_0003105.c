yank(void)
{ if (isProtected()==MSFalse&&yankBuffer().length()>0) insertString(yankBuffer().string()); }
