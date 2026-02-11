expand_variables(char **buff, const char *src)

{   const size_t srclen = strlen(src);
    enum { S_PLAIN, S_VAR };
    const char *curs = src;
    char *varname, *varp;
    int literal = 0;
    unsigned state;
    cm_string_t *result;

    result = cm_str_alloc(64);

    state = S_PLAIN;
    varname = (char*)malloc(srclen * 2);
    for (curs=src; *curs!='\0'; ++curs) {
        if (!literal && *curs == '\\') {
            literal = 1;
            continue;
        }

        switch (state) {
            case S_PLAIN:
                if (!literal && curs[0] == '$' && curs[1] == '(') {

                    state = S_VAR;
                    varp = varname;
                    ++curs;
                } else {

                    cm_str_append_char(result, *curs);
                }
                break;
            case S_VAR:
                if (!literal && *curs == ')') {

                    *varp = '\0';
                    cm_str_append_str(result, query_variable(varname));
                    state = S_PLAIN;
                } else {

                    *varp = *curs;
                    ++varp;
                }
                break;
            default:
                break;
        }

        literal = 0;
    }
    free((void*)varname);

    if (*buff != NULL) free((void*)(*buff));
    *buff = cm_str_strip(result);
}
