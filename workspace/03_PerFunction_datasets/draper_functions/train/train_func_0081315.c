unctrl(int c)
{
    static char     buffer[30];

    if (c < 0 || c >= 256)
	snprintf(buffer, sizeof(buffer), "%d", c);
    else
    {
	int             cc;

	switch (c)
	{
	case '\a':
	    cc = 'a';
	    goto escaped;

	case '\b':
	    cc = 'b';
	    goto escaped;

	case '\f':
	    cc = 'f';
	    goto escaped;

	case '\n':
	    cc = 'n';
	    goto escaped;

	case '\r':
	    cc = 'r';
	    goto escaped;

	case '\t':
	    cc = 't';
	    goto escaped;

	case '\v':
	    cc = 'v';
	    goto escaped;


	case '\'':
	case '\\':
	    cc = c;
	    escaped:
	    snprintf(buffer, sizeof(buffer), "0x%02X '\\%c'", c, cc);
	    break;

	case ' ': case '!': case '"': case '#':
	case '$': case '%': case '&':
	case '(': case ')': case '*': case '+':
	case ',': case '-': case '.': case '/':
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
	case '8': case '9': case ':': case ';':
	case '<': case '=': case '>': case '?':
	case '@': case 'A': case 'B': case 'C':
	case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K':
	case 'L': case 'M': case 'N': case 'O':
	case 'P': case 'Q': case 'R': case 'S':
	case 'T': case 'U': case 'V': case 'W':
	case 'X': case 'Y': case 'Z': case '[':
		  case ']': case '^': case '_':
	case '`': case 'a': case 'b': case 'c':
	case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k':
	case 'l': case 'm': case 'n': case 'o':
	case 'p': case 'q': case 'r': case 's':
	case 't': case 'u': case 'v': case 'w':
	case 'x': case 'y': case 'z': case '{':
	case '|': case '}': case '~':
	    snprintf(buffer, sizeof(buffer), "0x%02X '%c'", c, c);
	    break;

	default:
	    snprintf(buffer, sizeof(buffer), "0x%02X '\\%o'", c, c);
	    break;
	}
    }
    return buffer;
}
