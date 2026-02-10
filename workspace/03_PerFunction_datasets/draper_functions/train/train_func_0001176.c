decode_quoted_printable(char *dest,
				       char *src,
				       size_t *size)
{
    int cc;
    size_t i=0;

    while (*src != 0 && i < *size) {
	if (*src == '=') {

	    src++;
	    if (!*src) {
		break;
	    }


	    if ((*src == '\n') || (*src == '\r')){
		src++;
		if ((*src == '\n') || (*src == '\r')){
		    src++;
		}
		continue;
	    }

	    cc  = isdigit(*src) ? (*src - '0') : (*src - 55);
	    cc *= 0x10;
	    src++;
	    if (!*src) {
		break;
	    }
	    cc += isdigit(*src) ? (*src - '0') : (*src - 55);

	    *dest = cc;

	} else {
	    *dest = *src;
	}

	dest++;
	src++;
	i++;
    }

    *dest = '\0';

    *size = i;
    return(dest);
}
