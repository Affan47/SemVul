parse_header_block(const char* buf, qfits_header* hdr, int* found_it) {
    char getval_buf[FITS_LINESZ+1];
    char getkey_buf[FITS_LINESZ+1];
    char getcom_buf[FITS_LINESZ+1];
    char line_buf[FITS_LINESZ+1];

    int i;
    const char* line = buf;
    for (i=0; i<FITS_NCARDS; i++) {
        char *key, *val, *comment;
        debug("Looking at line %i:\n  %.80s\n", i, line);

        if (!strcmp(line, blankline))
            continue;
        key = qfits_getkey_r(line, getkey_buf);
        if (!key)
            return -1;
        val = qfits_getvalue_r(line, getval_buf);
        comment = qfits_getcomment_r(line, getcom_buf);
        debug("Got key/value/comment \"%s\" / \"%s\" / \"%s\"\n", key, val, comment);
        memcpy(line_buf, line, FITS_LINESZ);
        line_buf[FITS_LINESZ] = '\0';
        qfits_header_append(hdr, key, val, comment, line_buf);
        line += 80;
        if (!strcmp(key, "END")) {
            debug("Found END!\n");
            *found_it = 1;
            break;
        }
    }
    return 0;
}
