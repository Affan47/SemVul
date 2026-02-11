TIFFWriteShortArray(TIFF* tif, TIFFDirEntry* dir, uint16* v)
{
        if (dir->tdir_count <= 2) {
                if (tif->tif_header.tiff_magic == TIFF_BIGENDIAN) {
                        dir->tdir_offset = (uint32) ((long) v[0] << 16);
                        if (dir->tdir_count == 2)
                                dir->tdir_offset |= v[1] & 0xffff;
                } else {
                        dir->tdir_offset = v[0] & 0xffff;
                        if (dir->tdir_count == 2)
                                dir->tdir_offset |= (long) v[1] << 16;
                }
                return (1);
        } else
                return (TIFFWriteData(tif, dir, (char*) v));
}
