_krb5_debug(krb5_context context,
	    int level,
	    const char *fmt,
	    ...)
    __attribute__((format (printf, 3, 4)))
{
    va_list ap;

    if (context == NULL || context->debug_dest == NULL)
	return;

    va_start(ap, fmt);
    krb5_vlog(context, context->debug_dest, level, fmt, ap);
    va_end(ap);
}
