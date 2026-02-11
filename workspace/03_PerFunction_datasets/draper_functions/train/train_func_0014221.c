gtStripContig(TIFFRGBAImage* img, uint32* raster, uint32 w, uint32 h)
{
    TIFF* tif = img->tif;
    tileContigRoutine put = img->put.contig;
    uint32 row, y, nrow, rowstoread;
    uint32 pos;
    unsigned char* buf;
    uint32 rowsperstrip;
    uint32 imagewidth = img->width;
    tsize_t scanline;
    int32 fromskew, toskew;
    int ret = 1, flip;

    buf = (unsigned char*) _TIFFmalloc(TIFFStripSize(tif));
    if (buf == 0) {
                TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif), "No space for strip buffer");
                return (0);
    }
    _TIFFmemset(buf, 0, TIFFStripSize(tif));

    flip = setorientation(img);
    if (flip & FLIP_VERTICALLY) {
            y = h - 1;
            toskew = -(int32)(w + w);
    } else {
            y = 0;
            toskew = -(int32)(w - w);
    }

    TIFFGetFieldDefaulted(tif, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);
    scanline = TIFFScanlineSize(tif);
    fromskew = (w < imagewidth ? imagewidth - w : 0);
    for (row = 0; row < h; row += nrow)
    {
        rowstoread = rowsperstrip - (row + img->row_offset) % rowsperstrip;
        nrow = (row + rowstoread > h ? h - row : rowstoread);
        if (TIFFReadEncodedStrip(tif,
                                 TIFFComputeStrip(tif,row+img->row_offset, 0),
                                 buf,
                                 ((row + img->row_offset)%rowsperstrip + nrow) * scanline) < 0
            && img->stoponerr)
        {
            ret = 0;
            break;
        }

        pos = ((row + img->row_offset) % rowsperstrip) * scanline;
        (*put)(img, raster+y*w, 0, y, w, nrow, fromskew, toskew, buf + pos);
        y += (flip & FLIP_VERTICALLY ? -(int32) nrow : (int32) nrow);
    }

    if (flip & FLIP_HORIZONTALLY) {
            uint32 line;

            for (line = 0; line < h; line++) {
                    uint32 *left = raster + (line * w);
                    uint32 *right = left + w - 1;

                    while ( left < right ) {
                            uint32 temp = *left;
                            *left = *right;
                            *right = temp;
                            left++, right--;
                    }
            }
    }

    _TIFFfree(buf);
    return (ret);
}
