set_mtab_string_width (struct middletab *mt)
{
    int len, badkey = 0, maxlen = 0;
    int i, j;

    for (i=0, j=0; i<7; i++, j+=2) {
	if (!na(mt->val[j])) {
	    len = g_utf8_strlen(_(mt->key[j]), -1);
	    if (len > maxlen) {
		maxlen = len;
		badkey = j;
	    }
	    len = g_utf8_strlen(_(mt->key[j+1]), -1);
	    if (len > maxlen) {
		maxlen = len;
		badkey = j+1;
	    }
	}
    }

    if (maxlen > 22) {
	fprintf(stderr, "Can't make compact model stats table -- the max\n"
		"length translated string is %d chars, should be < 23\n",
		maxlen);
	fprintf(stderr, "offending string: '%s' ->\n '%s'\n",
		mt->key[badkey], _(mt->key[badkey]));
    }

    mt->mlen = maxlen;
}
