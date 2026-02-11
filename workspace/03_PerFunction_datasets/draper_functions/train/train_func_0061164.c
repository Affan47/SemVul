autobox_cleanup(pTHX_ void * unused) {
    PERL_UNUSED_VAR(unused);

    if (AUTOBOX_OP_MAP) {
        PTABLE_free(AUTOBOX_OP_MAP);
        AUTOBOX_OP_MAP = NULL;
    }
}
