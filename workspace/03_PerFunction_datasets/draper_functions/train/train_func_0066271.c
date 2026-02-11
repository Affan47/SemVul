__collect_line(void)
{
 register int32 c;
 register char *chp;
 int32 len;

 for (;;) { c = my_getc(__in_s); if (!vis_nonnl_white_(c)) break; }
 if (c == '\n' || c == EOF)
  {
   *__macwrkstr = '\0';
   my_ungetc_(c, __in_s);
   return;
  }
 for (chp = __macwrkstr, len = 0;;)
  {


   if (c == '\\')
    {
     if ((c = my_getc(__in_s)) == '\n') { c = ' '; __lin_cnt++; }
     else { my_ungetc_(c, __in_s); c = '\\'; }
    }
   addto_macwrkstr_(c);
   c = my_getc(__in_s);
   if (c == '\n' || c == EOF) { my_ungetc_(c, __in_s); break; }
  }

 *chp = '\0';
 __mac_line_len = len;
}
