GlobalByCookie(
       const Char * cookie )
{
  UInt i,top,bottom,middle;
  Int res;
  if (cookie == 0L)
    {
      Pr("Panic -- 0L cookie passed to GlobalByCookie\n",0L,0L);
      SyExit(2);
    }
  if (GlobalSortingStatus != 2)
    {
      for (i = 0; i < GlobalBags.nr; i++)
        {
          if (strcmp(cookie, GlobalBags.cookie[i]) == 0)
            return GlobalBags.addr[i];
        }
      return (Bag *)0L;
    }
  else
    {
      top = GlobalBags.nr;
      bottom = 0;
      while (top >= bottom) {
        middle = (top + bottom)/2;
        res = strcmp(cookie,GlobalBags.cookie[middle]);
        if (res < 0)
          top = middle-1;
        else if (res > 0)
          bottom = middle+1;
        else
          return GlobalBags.addr[middle];
      }
      return (Bag *)0L;
    }
}
