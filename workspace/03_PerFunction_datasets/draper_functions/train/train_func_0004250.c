debug_print (string s) const
{
  if (gi == NULL)
    cerr << s << endl;
  else
    gi->debug_print (s);
}
