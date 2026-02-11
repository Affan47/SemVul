MatchGroups(const char *g, int len, const char *pattern, bool exactmatch)
{
    char *group, *groups, *q;
    int i, lastwhite;
    enum uwildmat matched;
    bool wanted = false;

    q = groups = xmalloc(len + 1);
    for (lastwhite = -1,  i = 0 ; i < len ; i++) {

	if (g[i] == '\r' || g[i] == '\n' || g[i] == ' ' || g[i] == '\t') {
	    if (lastwhite + 1 != i)
	        *q++ = ' ';
	    lastwhite = i;
	} else
	    *q++ = g[i];
    }
    *q = '\0';

    group = strtok(groups, " ,");
    while (group != NULL) {
        q = strchr(group, ':');
        if (q != NULL)
            *q = '\0';
        matched = uwildmat_poison(group, pattern);
        if (matched == UWILDMAT_POISON || (exactmatch && !matched)) {
	    free(groups);
	    return false;
	}
        if (matched == UWILDMAT_MATCH)
            wanted = true;
        group = strtok(NULL, " ,");
    }

    free(groups);
    return wanted;
}
