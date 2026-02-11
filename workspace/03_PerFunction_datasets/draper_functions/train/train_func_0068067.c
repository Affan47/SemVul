SlurpDollarEquation(void)


{
    int brace = 0;
    int slash = 0;
    int i;
    char *s, *t, *u;

    s = (char *) malloc(1024 * sizeof(char));
    t = s;

    for (i = 0; i < 1024; i++) {
        *t = getTexChar();
        if (*t == '\\')
            slash++;
        else if (*t == '{' && even(slash) &&
          !(i > 5 && strncmp(t - 5, "\\left{", 6) == 0) && !(i > 6 && strncmp(t - 6, "\\right{", 7) == 0))
            brace++;
        else if (*t == '}' && even(slash) &&
          !(i > 5 && !strncmp(t - 5, "\\left}", 6)) && !(i > 6 && !strncmp(t - 6, "\\right}", 7)))
            brace--;
        else if (*t == '$' && even(slash) && brace == 0) {
            break;
        } else
            slash = 0;
        t++;
    }
    *t = '\0';

    u = strdup(s);
    free(s);
    return u;
}
