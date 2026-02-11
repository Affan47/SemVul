get_Model( char *pm )
{
    static char _s_buf[MAX_MODEL_NAME_LEN+4];
    int i, c, len;
    char *cp = _s_buf;
    char *model = pm;
    len = MAX_MODEL_NAME_LEN;
    for (i = 0; i < len; i++) {
        c = pm[i];
        if (c == '/')
            model = &pm[i+1];
        else if (c == 0)
            break;
    }
    strcpy(cp,model);
    len = (int)strlen(cp);
    model = 0;
    for (i = 0; i < len; i++) {
        c = cp[i];
        if (c == '.')
            model = &cp[i];
    }
    if (model)
        *model = 0;
    return cp;
}
