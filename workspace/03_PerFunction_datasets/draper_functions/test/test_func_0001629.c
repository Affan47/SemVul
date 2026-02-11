iran(struct csa *csa, int ilow, int ihigh)
{     int ixhi, ixlo, ixalo, leftlo, ixahi, ifulhi, irtlo, iover,
         irthi, j;
      ixhi = jran / i16;
      ixlo = jran - ixhi * i16;
      ixalo = ixlo * mult;
      leftlo = ixalo / i16;
      ixahi = ixhi * mult;
      ifulhi = ixahi + leftlo;
      irtlo = ixalo - leftlo * i16;
      iover = ifulhi / i15;
      irthi = ifulhi - iover * i15;
      jran = ((irtlo - modul) + irthi * i16) + iover;
      if (jran < 0) jran += modul;
      j = ihigh - ilow + 1;
      if (j > 0)
         return jran % j + ilow;
      else
         return ihigh;
}
