std_get_alpha(TokenStream *ts, char *token)
{
    int i = 0;
    char *t = ts->t;
    while (t[i] != '\0' && isalnum(t[i])) {
        if (i < MAX_WORD_SIZE) {
            token[i] = t[i];
        }
        i++;
    }
    return i;
}
