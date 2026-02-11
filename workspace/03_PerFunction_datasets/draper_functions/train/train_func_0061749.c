refdup_word(char **p)
{
    char *sp = *p;
    char *ep = sp;

    while (*ep && !my_isspace(*ep))
	ep++;

    *p = ep;
    return refstrndup(sp, ep - sp);
}
