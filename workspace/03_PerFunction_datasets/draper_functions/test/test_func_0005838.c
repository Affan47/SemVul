gs_tifsSizeProc(thandle_t fd)
{
    tifs_io_private *tiffio = (tifs_io_private *)fd;
    uint64_t length;
    gs_offset_t curpos = gp_ftell_64(tiffio->f);

    if (curpos < 0) {
        return(0);
    }

    if (gp_fseek_64(tiffio->f, (gs_offset_t)0, SEEK_END) < 0) {
        return(0);
    }
    length = (uint64_t)gp_ftell_64(tiffio->f);

    if (gp_fseek_64(tiffio->f, curpos, SEEK_SET) < 0) {
        return(0);
    }
    return length;
}
