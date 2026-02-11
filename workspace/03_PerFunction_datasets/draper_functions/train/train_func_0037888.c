FileTok(struct parse_state *ps,char *sep, int newline, char** token)
{
    char *current = ps->current;
    char *tp = &ps->token[0];


    do {


        if (current == NULL || *current == '\0' || (newline & FORCE_NEWLINE)) {
           if (!ps->filename || !_dxf_getline(ps))
              return ERROR;
           current = ps->line;
        }


        while (*current && strchr(sep,*current))
            current++;
    } while ((newline & NEWLINE_OK) && !*current);

    if (*current) {


        if (*current == '\"'){
           do {
                *tp = *current;
                tp++; current++;
              }while (*current && *current!='\"');
        }
        do {
                *tp = *current;
                tp++; current++;


        } while (*current && !strchr(sep,*current));
        *tp = '\0';
        *token = &ps->token[0];
    } else {

        *token = NULL;
    }

    ps->current = current;
    return OK;
}
