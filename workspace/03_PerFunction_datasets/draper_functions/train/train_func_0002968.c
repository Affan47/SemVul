getVarbinds(FILE * fp, struct varbind_list **retp)
{
    int             type;
    char            token[MAXTOKEN];

    struct varbind_list *mylist = NULL;
    struct varbind_list **mypp = &mylist;

    free_varbinds(retp);

    type = get_token(fp, token, MAXTOKEN);

    if (type != LEFTBRACKET) {
        return NULL;
    }

    type = get_token(fp, token, MAXTOKEN);
    while (type != RIGHTBRACKET && type != ENDOFFILE) {
        if ((type == LABEL) || (type & SYNTAX_MASK)) {
            *mypp =
                (struct varbind_list *) calloc(1,
                                               sizeof(struct
                                                      varbind_list));
            if (*mypp) {
                (*mypp)->vblabel = strdup(token);
                mypp = &(*mypp)->next;
            }
        }
        type = get_token(fp, token, MAXTOKEN);
    }

    *retp = mylist;
    return mylist;
}
