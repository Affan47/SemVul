qfits_is_table(const char* filename, int ext) {
    int rtn;
    anqfits_t* anq = anqfits_open_hdu(filename, ext);
    if (!anq) {
        fprintf(stderr, "qfits_is_table: failed to open \"%s\"", filename);
        return -1;
    }
    rtn = anqfits_is_table(anq, ext);
    anqfits_close(anq);
    return rtn;
}
