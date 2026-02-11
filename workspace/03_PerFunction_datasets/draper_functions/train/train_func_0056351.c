hexec_action_parse_fname_match(struct hexec_parser* p, int* action, int type, bool case_insensitive)
{
    if(p->cur_arg >= p->args->argc)
    {
        hexec_error("expression misses argument\n");
        return false;
    }
    char* str = p->args->argv[p->cur_arg++];
    struct hexec_expr* e;
    alloc_expr(p, action, &e);
    e->type = type;
    e->case_insensitive = case_insensitive;
    e->str = hexec_buf_alloc(p->buf, strlen(str) + 1);

    char* str2 = p->buf->buf + e->str;
    strcpy(str2, str);

    if(type == hexec_expr_contains && case_insensitive)
    {


        for(int i = 0; str2[i]; i++)
            str2[i] = tolower(str2[i]);
    }

    return true;
}
