to_c(const char *fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    if (vfprintf(c_file,fmt,ap) == EOF) {
	perror("write");
	exit(1);
    }
    va_end(ap);
}
