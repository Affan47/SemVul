js_printf(JSPrinter *jp, const char *format, ...)
{
    va_list ap;
    char *bp, *fp;
    int cc;

    if (*format == '\0')
        return 0;

    va_start(ap, format);


    if (*format == '\t') {
        format++;
        if (jp->pretty && Sprint(&jp->sprinter, "%*s", jp->indent, "") < 0)
            return -1;
    }


    fp = NULL;
    if (!jp->pretty && format[cc = strlen(format) - 1] == '\n') {
        fp = JS_strdup(jp->sprinter.context, format);
        if (!fp)
            return -1;
        fp[cc] = '\0';
        format = fp;
    }


    bp = JS_vsmprintf(format, ap);
    if (fp) {
        jp->sprinter.context->free(fp);
        format = NULL;
    }
    if (!bp) {
        JS_ReportOutOfMemory(jp->sprinter.context);
        return -1;
    }

    cc = strlen(bp);
    if (SprintPut(&jp->sprinter, bp, (size_t)cc) < 0)
        cc = -1;
    js_free(bp);

    va_end(ap);
    return cc;
}
