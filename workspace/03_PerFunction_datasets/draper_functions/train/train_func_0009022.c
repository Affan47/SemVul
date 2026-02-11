DumpModeDecode(TIFF* tif, tidata_t buf, tsize_t cc, tsample_t s)
{
  (void) s;
  if (tif->tif_rawcc < cc) {
    TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
        "DumpModeDecode: Not enough data for scanline %d",
        tif->tif_row);
    return (0);
  }


  if (tif->tif_rawcp != buf)
    _TIFFmemcpy(buf, tif->tif_rawcp, cc);
  tif->tif_rawcp += cc;
  tif->tif_rawcc -= cc;
  return (1);
}
