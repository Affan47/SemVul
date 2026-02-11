add_with_affix(const char * word, const char * example)
{

    struct hentry * dp = lookup(example);
    remove_forbidden_flag(word);
    if (dp && dp->astr) {
        int captype;
        int wbl = strlen(word);
        int wcl = get_clen_and_captype(word, wbl, &captype);
	if (aliasf) {
	    add_word(word, wbl, wcl, dp->astr, dp->alen, NULL, false);
	} else {
    	    unsigned short * flags = (unsigned short *) malloc (dp->alen * sizeof(short));
	    if (flags) {
		memcpy((void *) flags, (void *) dp->astr, dp->alen * sizeof(short));
		add_word(word, wbl, wcl, flags, dp->alen, NULL, false);
	    } else return 1;
	}
    	return add_hidden_capitalized_word((char *) word, wbl, wcl, dp->astr, dp->alen, NULL, captype);
    }
    return 1;
}
