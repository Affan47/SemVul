fl_popup_entry_set_subpopup( FL_POPUP_ENTRY * entry,
                             FL_POPUP       * subpopup )
{
    FL_POPUP *old_sub;

    if ( fli_check_popup_entry_exists( entry ) )
    {
        M_err( "fl_popup_entry_set_subpopup", "Invalid entry argument" );
        return NULL;
    }

    if ( entry->type != FL_POPUP_SUB )
    {
        M_err( "fl_popup_entry_set_subpopup", "Entry isn't a subpopup entry" );
        return NULL;
    }

    if ( entry->sub == subpopup )
        return entry->sub;

    if ( entry->sub->win != None || subpopup->win != None )
    {
        M_err( "fl_popup_entry_set_subpopup", "Can't change sub-popup while "
               "entries sub-popup is shown.");
        return NULL;
    }

    old_sub = entry->sub;
    entry->sub = subpopup;
    if ( check_sub( entry ) )
    {
        entry->sub = old_sub;
        M_err( "fl_popup_entry_set_subpopup", "Invalid sub-popup argument" );
        return NULL;
    }

    fl_popup_delete( entry->sub );
    return entry->sub = subpopup;
}
