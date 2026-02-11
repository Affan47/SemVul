putc_entity(int  ch,
            FILE *fp)
{
  if (ch == '&')
    fputs("&amp;", fp);
  else if (ch == '<')
    fputs("&lt;", fp);
  else
    putc(ch, fp);
}
