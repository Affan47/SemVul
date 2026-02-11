xargs(char *args)
{
    Agdesc_t desc = Agdirected;
    char c;

    while ((c = *args++)) {
	switch (c) {
	case 'u':
	case 'U':
	    desc.directed = 0;
	    break;
	case 'd':
	case 'D':
	    desc.directed = 1;
	    break;
	case 's':
	case 'S':
	    desc.strict = 1;
	    break;
	case 'n':
	case 'N':
	    desc.directed = 0;
	    break;
	default:
	    error(ERROR_WARNING, "unknown graph descriptor '%c' : ignored",
		  c);
	    break;
	}
    }
    return desc;
}
