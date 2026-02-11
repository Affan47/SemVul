find_strtag(DLLIST * taglist, STRPTR name)
{
    DLNODE *nd = find_dlnode(taglist->first, (APTR) name, cmp_strtag);
    HSCTAG *tag = NULL;

    if (nd)
        tag = (HSCTAG *) nd->data;

    return (tag);
}
