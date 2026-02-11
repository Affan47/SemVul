SubstToken(char c)
#else
SubstToken(c)
    char c;
#endif
{
    switch (c) {
	case 'p':
	case 'P':
	    substTokenCount[(unsigned)c]++;
	    return ISNUMBER;
	case 'h':
	case 'c':
	case 'r':
	    substTokenCount[(unsigned)c]++;
	    return ISSTRING;
	default:
	    return ISNOTHING;
    }
}
