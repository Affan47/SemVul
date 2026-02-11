_dico_stderr_log_printer(int lvl, int exitcode, int errcode,
			 const char *fmt, va_list ap)
{
    fprintf(stderr, "%s: %s: ", dico_program_name, prefix[lvl & L_MASK]);
    vfprintf(stderr, fmt, ap);
    if (errcode)
	fprintf(stderr, ": %s", strerror(errcode));
    fprintf(stderr, "\n");
}
