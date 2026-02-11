pow5mult(Bigint *b, int k, Stack_alloc *alloc)
{
  Bigint *b1, *p5, *p51=NULL;
  int i;
  static int p05[3]= { 5, 25, 125 };
  my_bool overflow= FALSE;

  if ((i= k & 3))
    b= multadd(b, p05[i-1], 0, alloc);

  if (!(k>>= 2))
    return b;
  p5= p5_a;
  for (;;)
  {
    if (k & 1)
    {
      b1= mult(b, p5, alloc);
      Bfree(b, alloc);
      b= b1;
    }
    if (!(k>>= 1))
      break;

    if (overflow)
    {
      p51= mult(p5, p5, alloc);
      Bfree(p5, alloc);
      p5= p51;
    }
    else if (p5 < p5_a + P5A_MAX)
      ++p5;
    else if (p5 == p5_a + P5A_MAX)
    {
      p5= mult(p5, p5, alloc);
      overflow= TRUE;
    }
  }
  if (p51)
    Bfree(p51, alloc);
  return b;
}
