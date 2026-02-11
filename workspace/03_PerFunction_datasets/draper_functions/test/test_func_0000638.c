gretl_string_split (const char *s, int *n,
			   const char *sep)
{
    int i, k, m = count_fields(s, sep);
    char *word;
    char **S;

    *n = 0;

    if (m == 0) {
	return NULL;
    }

    S = strings_array_new(m);
    if (S == NULL) {
	return NULL;
    }

    if (sep == NULL) {
	sep = " ";
    }

    for (i=0; i<m; i++) {
	s += strspn(s, sep);
	k = strcspn(s, sep);
	word = gretl_strndup(s, k);
	if (word == NULL) {
	    strings_array_free(S, m);
	    return NULL;
	}
	S[i] = word;
	s += k;
    }

    *n = m;

    return S;
}
