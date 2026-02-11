JPEGResetUpsampled( TIFF* tif )
{
  JPEGState* sp = JState(tif);
  TIFFDirectory* td = &tif->tif_dir;


  tif->tif_flags &= ~TIFF_UPSAMPLED;
  if (td->td_planarconfig == PLANARCONFIG_CONTIG) {
    if (td->td_photometric == PHOTOMETRIC_YCBCR &&
        sp->jpegcolormode == JPEGCOLORMODE_RGB) {
      tif->tif_flags |= TIFF_UPSAMPLED;
    } else {
#ifdef notdef
      if (td->td_ycbcrsubsampling[0] != 1 ||
          td->td_ycbcrsubsampling[1] != 1)
        ;
#endif
    }
  }


        if( tif->tif_tilesize > 0 )
            tif->tif_tilesize = isTiled(tif) ? TIFFTileSize(tif) : (tmsize_t)(-1);
        if( tif->tif_scanlinesize > 0 )
            tif->tif_scanlinesize = TIFFScanlineSize(tif);
}
