replace(Sfio_t * s, char *base, register char *repl, int ng, int *sub)
{
	char c;
	int idx, offset;

	while ((c = *repl++)) {
	if (c == '\\') {
	    if ((c = *repl) && isdigit(c)) {
			idx = c - '0';
			if (idx < ng) {
		    	offset = sub[2 * idx];
		    	sfwrite(s, base + offset, sub[2 * idx + 1] - offset);
			}
			repl++;
	    } else
			sfputc(s, '\\');
	} else
	    sfputc(s, c);
	}
}
