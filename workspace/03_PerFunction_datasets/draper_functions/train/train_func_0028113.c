get_alphabet()
{
  g_message("Getting alphabet");


  gchar *alphabet = _("a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/w/x/y/z");
  g_assert(g_utf8_validate(alphabet, -1, NULL));


  letterlist = g_strsplit (alphabet,"/",-1);
  guint i =-1;
  while (letterlist[++i])
  {
      ;
  }
  alphlen=i;
}
