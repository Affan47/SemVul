bug_on(struct error *err, const char *srcfile, int srclineno,
            const char *format, ...) {
    char *msg = NULL;
    int r;
    va_list ap;

    if (err->code != AUG_NOERROR)
        return;

    va_start(ap, format);
    vreport_error(err, AUG_EINTERNAL, format, ap);
    va_end(ap);

    if (err->details == NULL) {
        xasprintf(&err->details, "%s:%d:internal error", srcfile, srclineno);
    } else {
        r = xasprintf(&msg, "%s:%d:%s", srcfile, srclineno, err->details);
        if (r >= 0) {
            free(err->details);
            err->details = msg;
        }
    }
}
