reverseTable(Aword adr, int len)
#else
static void reverseTable(adr, len)
     Aword adr;
     int len;
#endif
{
  Aword *e = &memory[adr];
  int i;

  if (adr != 0)
    while (!endOfTable(e)) {
      for (i = 0; i < len/sizeof(Aword); i++) {
	reverse(e);
	e++;
      }
    }
}
