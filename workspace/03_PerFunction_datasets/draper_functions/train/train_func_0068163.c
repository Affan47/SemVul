save_choice_attrib( FILE      * fp,
                    FL_OBJECT * ob )
{
    FL_OBJECT *defobj;
    SuperSPEC *defsp, *sp;
    int i;


    defobj = fl_create_choice( ob->type, 0, 0, 0, 0, "" );

    defsp = get_superspec( defobj );
    sp = get_superspec( ob );

    if ( sp->align != defsp->align )
        fprintf( fp, "    align: %s\n", align_name( sp->align, 0 ) );
    if ( sp->new_menuapi != defsp->new_menuapi )
        fprintf( fp, "    struct: %d\n", sp->new_menuapi );

    for ( i = 1; i <= sp->nlines; i++ )
    {
        fprintf( fp, "    content: %s\n", sp->content[ i ] );
        if ( sp->mode[ i ] != defsp->mode[ i ] )
            fprintf( fp, "    mode: %s\n", get_pupmode_name( sp->mode[ i ] ) );
        if ( sp->shortcut[ i ] && *sp->shortcut[ i ] )
            fprintf( fp, "    shortcut: %s\n", sp->shortcut[ i ] );
    }

    if ( sp->int_val != defsp->int_val )
        fprintf( fp, "    value: %d\n", sp->int_val );
}
