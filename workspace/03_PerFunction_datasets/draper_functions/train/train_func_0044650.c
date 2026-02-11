ACL_NameListDestroy(NSErr_t *errp, char **name_list)
{
    int			list_index;

    if ( name_list == NULL )
        return(ACLERRUNDEF);

    for ( list_index = 0; name_list[list_index]; list_index++ ) {
        PERM_FREE(name_list[list_index]);
    }
    PERM_FREE(name_list);
    return(0);
}
