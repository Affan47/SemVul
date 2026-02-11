get_cmdcomment(FILE *f)
{
 register int32 c;
 int32 c2;


 if ((c2 = getc(f)) == '/')
  {
   while ((c = getc(f)) != '\n') if (c == EOF) { ungetc(c, f); return(TRUE); }
   ungetc(c, f);
   return(TRUE);
  }

 if (c2 == '*')
  {
more_comment:
   while ((c = getc(f)) != '*')
    {
     if (c == EOF) { ungetc(c, f); return(TRUE); }
     if (c == '\n') __lin_cnt++;
     if (c == '/')
      {
       if ((c2 = getc(f)) == '*')
        {
         __pv_fwarn(622, "nested /* in /* style -f argument file comment");
         continue;
        }
       c = c2;
      }
    }

got_star:
   if ((c = getc(f)) == '/') return(TRUE);
   if (c == '*') goto got_star;
   if (c == '\n') __lin_cnt++;
   goto more_comment;
  }

 ungetc(c2, f);
 return(FALSE);
}
