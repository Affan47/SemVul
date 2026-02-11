stream_add_strsub(Stream *str, const char *source, const char *what, const char *with, int case_counts)
{
    int lwhat = strlen(what);

    while (*source) {
	if (!(case_counts ? strncmp(source, what, lwhat)
	      : mystrncasecmp(source, what, lwhat))) {
	    stream_add_string(str, with);
	    source += lwhat;
	} else
	    stream_add_char(str, *source++);
    }
}
