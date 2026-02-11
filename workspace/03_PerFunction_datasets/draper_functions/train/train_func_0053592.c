cleartoendofline (void)
{
  char ch;
  ch = getchar ();
  while (ch != '\n')
    ch = getchar ();
}
