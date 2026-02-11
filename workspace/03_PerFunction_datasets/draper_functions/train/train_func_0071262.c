test38_aux_bNread (void *buff, size_t elsize, size_t nelem, struct emuFile * f) {
    char * b = (char *) buff;
    int v;
    size_t i, j, c = 0;

    if (NULL == f || NULL == b) return c;
    for (i=0; i < nelem; i++) for (j=0; j < elsize; j++) {
        v = test38_aux_bNgetc (f);
        if (EOF == v) {
            *b = (char) '\0';
            return c;
        } else {
            *b = (char) v;
            b++;
            c++;
        }
    }

    return c;
}
