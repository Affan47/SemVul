regexp_release(struct regexp *regexp) {
    if (regexp != NULL && regexp->re != NULL) {
        regfree(regexp->re);
        FREE(regexp->re);
    }
}
