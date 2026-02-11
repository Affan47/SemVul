escapequotes (char *s)
{
    char *es;
    int i, k, n, len, elen;

    if (s == NULL)
        return NULL;

    len = strlen(s);
    es = (char *) malloc ((len + 1)*sizeof(char));
    strcpy(es, s);
    n = 0;
    while ((es = strchr(es, '\"'))) {
    	es++;
    	n++;
    }

    elen = len + n + 1;
    es = (char *) realloc (es, elen*sizeof(char));

    i = k = 0;
    while (i < len) {
        if (s[i] == '\"') {
            es[k] = '\\';
            k++;
        }
        es[k] = s[i];
        i++; k++;
    }
    es[elen-1] = '\0';
    return es;
}
