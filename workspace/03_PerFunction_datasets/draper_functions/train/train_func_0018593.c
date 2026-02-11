BYTE2WORD(unsigned char *b)
{
   ulong32 t;
   LOAD32L(t, b);
   return t;
}
