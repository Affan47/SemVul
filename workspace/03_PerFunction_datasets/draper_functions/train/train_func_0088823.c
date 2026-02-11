SweepWeakPointerObj( Bag *src, Bag *dst, UInt len)
{
  Bag elm;
  while (len --)
    {
      elm = *src++;
      *dst ++ = IS_WEAK_DEAD_BAG(elm) ? (Bag) 0 : elm;
    }
}
