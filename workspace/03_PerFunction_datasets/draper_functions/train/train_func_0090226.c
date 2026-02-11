markRange(int macro, char from, char to)
{
  int i;
  for (i = CHAR_MIN; i <= CHAR_MAX; i++)
    if (((unsigned char)i >= (unsigned char)from)
	&& ((unsigned char)i <= (unsigned char)to))
      NTL_char_attrib[(char)i - CHAR_MIN] |= macro;
}
