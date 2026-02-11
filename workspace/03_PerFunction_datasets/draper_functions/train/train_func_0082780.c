getbool(int c, int *int_r, gnc_t gnc, void *closure)
{
    char *t;
    int i;
    c = getword(c, &t, gnc, closure);
    if(c < -1)
        return c;
    if(strcmp(t, "true") == 0 || strcmp(t, "yes") == 0)
        i = CONFIG_YES;
    else if(strcmp(t, "false") == 0 || strcmp(t, "no") == 0)
        i = CONFIG_NO;
    else if(strcmp(t, "default") == 0 || strcmp(t, "auto") == 0)
        i = CONFIG_DEFAULT;
    else {
        free(t);
        return -2;
    }
    free(t);
    *int_r = i;
    return c;
}
