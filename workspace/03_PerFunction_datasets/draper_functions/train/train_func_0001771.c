Fax3Decode1D(TIFF* tif, uint8* buf, tmsize_t occ, uint16 s)
{
  DECLARE_STATE(tif, sp, "Fax3Decode1D");
  (void) s;
  if (occ % sp->b.rowbytes)
  {
    TIFFErrorExt(tif->tif_clientdata, module, "Fractional scanlines cannot be read");
    return (-1);
  }
  CACHE_STATE(tif, sp);
  thisrun = sp->curruns;
  while (occ > 0) {
    a0 = 0;
    RunLength = 0;
    pa = thisrun;
#ifdef FAX3_DEBUG
    printf("\nBitAcc=%08X, BitsAvail = %d\n", BitAcc, BitsAvail);
    printf("-------------------- %d\n", tif->tif_row);
    fflush(stdout);
#endif
    SYNC_EOL(EOF1D);
    EXPAND1D(EOF1Da);
    (*sp->fill)(buf, thisrun, pa, lastx);
    buf += sp->b.rowbytes;
    occ -= sp->b.rowbytes;
    sp->line++;
    continue;
  EOF1D:
    CLEANUP_RUNS();
  EOF1Da:
    (*sp->fill)(buf, thisrun, pa, lastx);
    UNCACHE_STATE(tif, sp);
    return (-1);
  }
  UNCACHE_STATE(tif, sp);
  return (1);
}
