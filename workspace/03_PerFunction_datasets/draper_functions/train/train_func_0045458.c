dbg_error(C *s,I idx)
{
  H("\343 dbg error: \"%s\" %s\n",s,s[idx]?"not recognized":"is ambiguous");
  FFL;
}
