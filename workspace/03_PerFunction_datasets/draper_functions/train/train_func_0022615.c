TIFFTileRowSize64(TIFF* tif)
{
  TIFFDirectory *td = &tif->tif_dir;
  uint64 rowsize;

  if (td->td_tilelength == 0 || td->td_tilewidth == 0)
    return (0);
  rowsize = _TIFFMultiply64(tif, td->td_bitspersample, td->td_tilewidth,
      "TIFFTileRowSize");
  if (td->td_planarconfig == PLANARCONFIG_CONTIG)
    rowsize = _TIFFMultiply64(tif, rowsize, td->td_samplesperpixel,
        "TIFFTileRowSize");
  return (TIFFhowmany8_64(rowsize));
}
