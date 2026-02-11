ick_rev_xor32(unsigned int n)
{
  unsigned int a=0, l=1, t=0;
  while(l<=0x4000000)
  {
    if(n&l)
      t^=1;
    if(t)
      a+=l*2;
    l*=2;
  }
  if(ick_xor32(a)==n) return a;
  ick_lose(IE277, ick_lineno, (const char*) NULL);
   return 0;
}
