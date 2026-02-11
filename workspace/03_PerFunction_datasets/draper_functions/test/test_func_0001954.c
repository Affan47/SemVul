copyarr(int *p) {
   int sz = *p ;
   while (sz & (sz - 1))
      sz &= sz - 1 ;
   sz *= 2 ;
   int *r = new int[sz] ;
   memcpy(r, p, sizeof(int) * (p[0] + 1)) ;
#ifdef SLOWCHECK
   for (int i=p[0]+1; i<sz; i++)
      r[i] = 0xdeadbeef ;
#endif
   return r ;
}
