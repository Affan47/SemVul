parity2(big x)
{
   if (x->len==0) return 0;
   return (int)(x->w[0]%2);
}
