cl_variants (vdepth, vcuri)
     int vdepth, vcuri;
{
  register int vardepi;

  vcuri--;
  for (vardepi = vdepth; vardepi >= 0; vardepi--) {
    de_activate (curvar[vcuri-vardepi]);
    strcpy (curvar[vcuri-vardepi], "");
    reset_pathlist ();
  }
}
