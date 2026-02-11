as_string() const
{
  char buf[32];
  if (branch || sequence)
    sprintf(buf, "%d.%d.%d.%d", rel, level, branch, sequence);
  else
    sprintf(buf, "%d.%d", rel, level);

  return mystring(buf);
}
