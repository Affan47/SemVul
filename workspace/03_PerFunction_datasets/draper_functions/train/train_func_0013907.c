fl_delete_menu_item( FL_OBJECT * ob,
                     int         numb )
{
    int i;
    FLI_MENU_SPEC *sp = ob->spec;

    if ( ISPUP( sp ) || ( numb = val_to_index( ob, numb ) ) <= 0 )
        return;

    fl_safe_free( sp->items[ numb ] );
    fl_safe_free( sp->shortcut[ numb ] );

    for ( i = numb; i < sp->numitems; i++ )
    {
        sp->items[ i ]      = sp->items[ i + 1 ];
        sp->mode[ i ]       = sp->mode[ i + 1 ];
        sp->modechange[ i ] = sp->modechange[ i + 1 ];
        sp->mval[ i ]       = sp->mval[ i + 1 ];
        sp->shortcut[ i ]   = sp->shortcut[ i + 1 ];
        sp->cb[ i ]         = sp->cb[ i + 1 ];
    }

    if ( sp->val == numb )
        sp->val = -1;

    sp->items[ sp->numitems ]      = NULL;
    sp->shortcut[ sp->numitems ]   = NULL;
    sp->mode[ sp->numitems ]       = FL_PUP_NONE;
    sp->modechange[ sp->numitems ] = 0;
    sp->mval[ sp->numitems ]       = 0;
    sp->cb[ sp->numitems ]         = NULL;

    sp->numitems--;
}
