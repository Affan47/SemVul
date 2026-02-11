app_strnode(DLLIST * list, STRPTR str)
{
    STRPTR scp = new_string_node(str);
    DLNODE *nd = NULL;

    if (scp)
    {
        nd = app_dlnode(list, (APTR) scp);
    }

    return nd;
}
