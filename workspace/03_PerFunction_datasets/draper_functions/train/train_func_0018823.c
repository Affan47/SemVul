getc_wrapper(FILE* fp )
#else
getc_wrapper(FILE* fp )
#endif
{
    int c;

    while (1) {
#ifdef USE_MOUSE
	if (term && term->waitforinput && interactive) {
	    c = term->waitforinput();
	}
	else
#endif
	if (fp)
	    c = getc(fp);
	else
	    c = getchar();
	if (c == EOF && errno == EINTR)
	    continue;
	return c;
    }
}
