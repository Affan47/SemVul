to_n_nary(C_uword num, C_uword base)
{
  char *p;
  static char digits[] ={ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
  buffer [ 66 ] = '\0';
  p = buffer + 66;

  do {
    *(--p) = digits [ num % base ];
    num /= base;
  } while (num);

  return p;
}
