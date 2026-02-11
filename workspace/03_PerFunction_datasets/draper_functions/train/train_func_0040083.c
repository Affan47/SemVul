GC_err_puts(const char *s)
{
    if (WRITE(GC_stderr, s, strlen(s)) < 0) ABORT("write to stderr failed");
}
