double_quote_position (const char *s)
{
    int i, j, ns, n = -1;

    for (i=0; s[i]; i++) {
	if (s[i] == '"') {
	    ns = 0;
	    for (j=i-1; j>=0; j--) {
		if (s[j] == '\\') {
		    ns++;
		} else {
		    break;
		}
	    }
	    if (ns % 2 == 0) {

		n = i;
		break;
	    }
	}
    }

    return n;
}
