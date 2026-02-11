TIFFReadRawTile1(TIFF* tif,
    ttile_t tile, tdata_t buf, tsize_t size, const char* module)
{
        TIFFDirectory *td = &tif->tif_dir;

        if (!isMapped(tif)) {
                tsize_t cc;

                if (!SeekOK(tif, td->td_stripoffset[tile])) {
                        TIFFErrorExt(tif->tif_clientdata, module,
                            "%s: Seek error at row %ld, col %ld, tile %ld",
                            tif->tif_name,
                            (long) tif->tif_row,
                            (long) tif->tif_col,
                            (long) tile);
                        return ((tsize_t) -1);
                }
                cc = TIFFReadFile(tif, buf, size);
                if (cc != size) {
                        TIFFErrorExt(tif->tif_clientdata, module,
            "%s: Read error at row %ld, col %ld; got %lu bytes, expected %lu",
                            tif->tif_name,
                            (long) tif->tif_row,
                            (long) tif->tif_col,
                            (unsigned long) cc,
                            (unsigned long) size);
                        return ((tsize_t) -1);
                }
        } else {
                if (td->td_stripoffset[tile] + size > tif->tif_size) {
                        TIFFErrorExt(tif->tif_clientdata, module,
    "%s: Read error at row %ld, col %ld, tile %ld; got %lu bytes, expected %lu",
                            tif->tif_name,
                            (long) tif->tif_row,
                            (long) tif->tif_col,
                            (long) tile,
                            (unsigned long) tif->tif_size - td->td_stripoffset[tile],
                            (unsigned long) size);
                        return ((tsize_t) -1);
                }
                _TIFFmemcpy(buf, tif->tif_base + td->td_stripoffset[tile], size);
        }
        return (size);
}
