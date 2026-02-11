dsgw_emits (const char* s)


{
    size_t n = strlen (s);
    if (n > 0 && dsgw_emitn (stdout, s, n) == NULL) {
	return EOF;
    }
    return n;
}
