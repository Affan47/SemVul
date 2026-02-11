parser_get_entries( PData *pd, const char *name, List   **result )
{
    PData *entry;
    *result = 0;
    if ( !parser_get_pdata( pd, name, &entry ) ) {
        sprintf( parser_sub_error, "parser_get_entries:\n %s", parser_error );
        strcpy( parser_error, parser_sub_error );
        return 0;
    }
    if ( !entry->entries || entry->entries->count == 0 ) {
        sprintf( parser_error, tr("parser_get_entries: %s/%s: no subtrees"), pd->name, name );
        return 0;
    }
    *result = entry->entries;
    return 1;
}
