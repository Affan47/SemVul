my_iconv(RESULT * result, RESULT * charset_from, RESULT * charset_to, RESULT * arg)
{
    char *source;
    size_t source_left;
    char *dest;
    char *dest_pos;
    size_t dest_left;
    iconv_t cd;

    source = R2S(arg);
    source_left = strlen(source);


    dest_left = 2 * source_left;
    dest = malloc(dest_left + 1);
    dest_pos = dest;

    cd = iconv_open(R2S(charset_to), R2S(charset_from));
    if (cd != (iconv_t) (-1)) {

	do {


	    if (iconv(cd, &source, &source_left, &dest_pos, &dest_left) == (size_t) (-1)) {
		switch (errno) {
		case EILSEQ:


		    info("plugin_iconv: illegal character in input string: %c", *source);
		    source_left--;
		    source++;
		    break;
		case EINVAL:


		    info("plugin_iconv: illegal character at end of input");
		    source_left = 0;
		    break;
		case E2BIG:


		    error
			("plugin_iconv: out of memory in destination buffer. Seems like Ernst was too lazy, complain to him!");
		    source_left = 0;
		    break;
		default:
		    error("plugin_iconv: strange errno state (%d) occurred", errno);
		    source_left = 0;
		}
	    }
	} while (source_left > 0);


	*dest_pos = 0;
	dest_pos++;

	iconv_close(cd);
    } else {
	error("plugin_iconv: could not open conversion descriptor. Check if your charsets are supported!");

	strcpy(dest, source);
    }

    SetResult(&result, R_STRING, dest);

    free(dest);
}
