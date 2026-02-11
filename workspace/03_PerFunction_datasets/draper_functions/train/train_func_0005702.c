listpictname(char *s)
{
  static rbool first_pict=1;

  if (s==NULL) {
    if (!first_pict) writeln("");
    first_pict=1;
    return;
  }
  if (first_pict) {
    writeln("");
    sysmsg(219,"  Illustrations:");
    first_pict=0;
  }
  writestr("  ");
  writestr(s);
}
