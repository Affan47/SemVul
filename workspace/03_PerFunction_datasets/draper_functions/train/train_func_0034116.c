xsh_sort_table_1(cpl_table *t, const char *column, cpl_boolean reverse)
{
    cpl_propertylist *plist = NULL;

    assure(t != NULL, CPL_ERROR_NULL_INPUT, "Null table");
    assure(cpl_table_has_column(t, column), CPL_ERROR_ILLEGAL_INPUT,
       "No column '%s'", column);

    check_msg(( plist = cpl_propertylist_new(),
        cpl_propertylist_append_bool(plist, column, reverse)),
       "Could not create property list for sorting");

    check_msg( cpl_table_sort(t, plist), "Could not sort table");

  cleanup:
    xsh_free_propertylist(&plist);
    return cpl_error_get_code();
}
