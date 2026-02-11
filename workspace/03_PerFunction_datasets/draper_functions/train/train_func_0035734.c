fl_clear_menu( FL_OBJECT * ob )
{
    int i;
    FLI_MENU_SPEC *sp = ob->spec;

    if ( ISPUP( sp ) )
    {
        fl_freepup( sp->extern_menu );
        sp->extern_menu = -1;
        return;
    }

    sp->val = 0;
    sp->cur_val = 0;

    for ( i = 1; i <= sp->numitems; i++ )
    {
        fl_safe_free( sp->items[ i ] );
        fl_safe_free( sp->shortcut[ i ] );
        sp->mode[ i ] = FL_PUP_NONE;
        sp->cb[ i ] = NULL;
    }

    sp->numitems = 0;
}
