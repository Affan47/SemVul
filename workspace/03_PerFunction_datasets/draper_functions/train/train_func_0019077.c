fli_popup_add_entries( FL_POPUP   * popup,
                       const char * entries,
                       va_list      ap,
                       const char * caller,
                       int          simple )
{
    FL_POPUP_ENTRY *new_entries,
                   *e;
    char *str;


    if ( entries == NULL )
    {
        M_err( caller, "NULL entries argument" );
        return NULL;
    }


    if ( fli_check_popup_exists( popup ) )
    {
        M_err( caller, "Popup does not exist" );
        return NULL;
    }


    if ( ( str = fl_strdup( entries ) ) == NULL )
    {
        M_err( caller, "Running out of memory" );
        return NULL;
    }

    new_entries = parse_entries( popup, str, ap, caller, simple );
    fl_free( str );


    if ( new_entries == NULL )
        return NULL;


    if ( popup->entries == NULL )
        popup->entries = new_entries;
    else
    {
        for ( e = popup->entries; e->next != NULL; e = e->next )
             ;
        e->next = new_entries;
        new_entries->prev = e;
    }


    setup_subpopups( popup );


    set_need_recalc( popup );


    return new_entries;
}
