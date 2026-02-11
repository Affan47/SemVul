morphprep(char *s)
{
    char *rest, *exc_word, *lastwd = NULL, *last;
    int i, offset, cnt;
    char word[WORDBUF], end[WORDBUF];
    static char retval[WORDBUF];

    if (strlen(s) > WORDBUF - 1)
        return (NULL);


    rest = strchr(s, '_');
    last = strrchr(s, '_');
    if (rest != last) {
	if ((lastwd = morphword(last + 1, NOUN)) != NULL) {
	    strncpy(end, rest, last - rest + 1);
	    end[last-rest+1] = '\0';
	    strcat(end, lastwd);
	}
    }

    strncpy(word, s, rest - s);
    word[rest - s] = '\0';
    for (i = 0, cnt = strlen(word); i < cnt; i++)
	if (!isalnum((unsigned char)(word[i]))) return(NULL);

    offset = offsets[VERB];
    cnt = cnts[VERB];


    if ((exc_word = exc_lookup(word, VERB)) &&
	strcmp(exc_word, word)) {

	sprintf(retval, "%s%s", exc_word, rest);
	if(is_defined(retval, VERB))
	    return(retval);
	else if (lastwd) {
	    sprintf(retval, "%s%s", exc_word, end);
	    if(is_defined(retval, VERB))
		return(retval);
	}
    }

    for (i = 0; i < cnt; i++) {
	if ((exc_word = wordbase(word, (i + offset))) &&
	    strcmp(word, exc_word)) {

	    sprintf(retval, "%s%s", exc_word, rest);
	    if(is_defined(retval, VERB))
		return(retval);
	    else if (lastwd) {
		sprintf(retval, "%s%s", exc_word, end);
		if(is_defined(retval, VERB))
		    return(retval);
	    }
	}
    }
    sprintf(retval, "%s%s", word, rest);
    if (strcmp(s, retval))
	return(retval);
    if (lastwd) {
	sprintf(retval, "%s%s", word, end);
	if (strcmp(s, retval))
	    return(retval);
    }
    return(NULL);
}
