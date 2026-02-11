ident(const char *str)
{
    TREE **walk;
    int diff;

    walk = &tree;
    while (*walk) {
        if (!(diff = strcmp(str,(*walk)->str))) return (*walk)->str;
        if (diff < 0) walk = &(*walk)->left;
        else walk = &(*walk)->right;
    }
    *walk = alloc(sizeof(TREE)+strlen(str)+1);
    (*walk)->left = (*walk)->right = NULL;
    strcpy((char *) (*walk)->str,str);
    return (*walk)->str;
}
