gui_show_conds()
{
    char str[128];
    int border = 10, i, j;
    int x = border, y = border;
    SDL_Surface *contents = gui->sinfo->contents;
    gui->font_std->align = ALIGN_X_LEFT | ALIGN_Y_TOP;
    SDL_FillRect( contents, 0, 0x0 );

    sprintf( str, tr("Explicit VicConds (%s)"),
             (vcond_check_type==VCOND_CHECK_EVERY_TURN)?tr("every turn"):tr("last turn") );
    write_line( contents, gui->font_std, str, x, &y ); y += 10;
    for ( i = 1; i < vcond_count; i++ ) {
        sprintf( str, "'%s':", vconds[i].message );
        write_line( contents, gui->font_std, str, x, &y );
        for ( j = 0; j < vconds[i].sub_and_count; j++ ) {
            if ( vconds[i].subconds_and[j].player )
                sprintf( str, tr("AND %.2s "), vconds[i].subconds_and[j].player->name );
            else
                sprintf( str, tr("AND -- ") );
            gui_render_subcond( &vconds[i].subconds_and[j], str + 7 );
            write_line( contents, gui->font_std, str, x, &y );
        }
        for ( j = 0; j < vconds[i].sub_or_count; j++ ) {
            if ( vconds[i].subconds_or[j].player )
                sprintf( str, tr("OR %.2s "), vconds[i].subconds_or[j].player->name );
            else
                sprintf( str, tr("OR -- ") );
            gui_render_subcond( &vconds[i].subconds_or[j], str + 6 );
            write_line( contents, gui->font_std, str, x, &y );
        }
    }
    y += 6;

    sprintf( str, tr("else: '%s'"), vconds[0].message );
    write_line( contents, gui->font_std, str, x, &y );

    frame_apply( gui->sinfo );
    frame_hide( gui->sinfo, 0 );
}
