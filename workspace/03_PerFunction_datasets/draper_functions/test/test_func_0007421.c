doquad01(supertile *zis, supertile *edge,
                        supertile *par, supertile *cor, int lev) {


   poller->poll() ;
   int changing = (zis->flags | (par->flags >> 19) |
                   (((edge->flags >> 18) | (cor->flags >> 27)) & 1)) & 0xff ;
   int x, b, nchanging = (zis->flags & 0x3ff00) << 10 ;
   supertile *p, *pf, *pu, *pfu ;
   STAT(ds++) ;


   if (changing & 1) {
      x = 7 ;
      b = 1 ;
      pf = edge->d[0] ;
      pfu = cor->d[0] ;
   } else {


      b = (changing & - changing) ;
      x = 7 - ai[b] ;
      pf = zis->d[x + 1] ;
      pfu = par->d[x + 1] ;
   }
   for (;;) {
      p = zis->d[x] ;
      pu = par->d[x] ;


      if (changing & b) {


         if (zis->d[x] == nullroots[lev-1])
            p = zis->d[x] = (lev == 1 ? (supertile *)newtile() :
                                                      newsupertile(lev-1)) ;


         nchanging |= ((lev == 1) ? p01((tile *)p, (tile *)pf,
                                        (tile *)pu, (tile *)pfu) :
                                    doquad01(p, pu, pf, pfu, lev-1)) << x ;
         changing -= b ;
      } else if (changing == 0)
         break ;
      b <<= 1 ;
      x-- ;
      pfu = pu ;
      pf = p ;
   }
   zis->flags = nchanging | 0xf0000000 ;
   return upchanging(nchanging) ;
}
