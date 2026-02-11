allocdistpfxidxcounts(GtBcktab *bcktab,unsigned int prefixlength,
                                  GtLogger *logger)
{
  gt_assert(bcktab->withspecialsuffixes);
  if (prefixlength > 2U)
  {
    if (bcktab->numofdistpfxidxcounters > 0)
    {
      unsigned long *ulongcounters;
      uint32_t *uintcounters;
      size_t allocsize;

      if (bcktab->useulong)
      {
        bcktab->ulongdistpfxidx = gt_malloc(sizeof (void *) * (prefixlength-1));
        allocsize = sizeof (*ulongcounters) * bcktab->numofdistpfxidxcounters;
        ulongcounters = gt_malloc(allocsize);
        memset(ulongcounters,0,allocsize);
        ulong_setdistpfxidxptrs(bcktab->ulongdistpfxidx,ulongcounters,
                                bcktab->basepower,prefixlength);
      } else
      {
        bcktab->uintdistpfxidx = gt_malloc(sizeof (void *) * (prefixlength-1));
        allocsize = sizeof (*uintcounters) * bcktab->numofdistpfxidxcounters;
        uintcounters = gt_malloc(allocsize);
        memset(uintcounters,0,allocsize);
        uint_setdistpfxidxptrs(bcktab->uintdistpfxidx,uintcounters,
                               bcktab->basepower,prefixlength);
      }
      gt_logger_log(logger,"sizeof (distpfxidx)=%lu bytes",
                            (unsigned long) allocsize);
    }
  }
}
