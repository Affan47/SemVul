code(const char *fmt,...)
{
    va_list ap;

    va_start(ap,fmt);
    while (*fmt)
	if (*fmt++ == '%') {
	    switch (*fmt++) {
		case 'd':
		    put_item(itos(va_arg(ap,int)));
		    break;
		case 's':
		    put_item(va_arg(ap,const char *));
		    break;
		default:
		    die("invalid format character %c",fmt[-1]);
	    }
	}
	else {
	    const char *here;

	    here = strchr(--fmt,'%');
	    if (!here) append_last(fmt);
	    else {
		char buffer[200];

		if (here[1] != 's') die("bad format in extension");
		strncpy(buffer,fmt,(size_t) (here-fmt));
		strcpy(buffer+(here-fmt),va_arg(ap,const char *));
		strcat(buffer,here+2);
		append_last(stralloc(buffer));
	    }
	    break;
	}
    va_end(ap);
}
