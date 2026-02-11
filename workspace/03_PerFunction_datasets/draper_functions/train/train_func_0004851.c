c_complete(void)
{
    char        *p, *q;
    char        *word, *new;
    size_t      len;
    int         unique;
    el_status_t s = 0;

    word = el_find_word();
    p = (char *)rl_complete((char *)word, &unique);
    if (word)
        free(word);
    if (p) {
        len = strlen((char *)p);
        word = p;
        new = q = malloc(sizeof(char) * (2 * len + 1));
	if (!new)
	    return CSstay;
        while (*p) {
            if ((*p < ' ' || strchr(SEPS, (char) *p) != NULL)
                                && (!unique || p[1] != 0)) {
                *q++ = '\\';
            }
            *q++ = *p++;
        }
        *q = '\0';
        free(word);
        if (len > 0) {
            s = insert_string(new);
#ifdef CONFIG_ANNOYING_NOISE
            if (!unique)
                el_ring_bell();
#endif
        }
        free(new);
        if (len > 0)
	    return s;
    }
    return c_possible();
}
