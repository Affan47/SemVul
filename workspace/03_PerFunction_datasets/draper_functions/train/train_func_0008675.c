growsbuf (int ssize) {
    int nsize;

    nsize = ((sbufn + ssize) / SBUFINCR + 1) * SBUFINCR;
    if (!(sbufp = realloc (sbufp, nsize * SBUFSIZE)))
        panic1 (POS, "growsbuf", "sbuf realloc failed");
    sbufn = nsize;
}
