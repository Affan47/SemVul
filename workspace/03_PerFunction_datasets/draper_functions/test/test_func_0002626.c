print_string(FILE* fp, const ETERM* ep)
{
    int ch_written = 0;

    putc('"', fp);
    ch_written++;
    while (ERL_IS_CONS(ep)) {
	int c = ERL_INT_VALUE(HEAD(ep));

	if (c >= ' ') {
	    putc(c, fp);
	    ch_written++;
	}
	else {
	    switch (c) {
	    case '\n': fputs("\\n", fp); ch_written += 2; break;
	    case '\r': fputs("\\r", fp); ch_written += 2; break;
	    case '\t': fputs("\\t", fp); ch_written += 2; break;
	    case '\v': fputs("\\v", fp); ch_written += 2; break;
	    case '\b': fputs("\\b", fp); ch_written += 2; break;
	    case '\f': fputs("\\f", fp); ch_written += 2; break;
		break;
	    default:
		ch_written += fprintf(fp, "\\%o", c);
		break;
	    }
	}
	ep = TAIL(ep);
    }
    putc('"', fp);
    ch_written++;
    return ch_written;
}
