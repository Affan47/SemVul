gui_show_quick_info( Frame *qinfo, Unit *unit )
{
    int i, len;
    char str[64];

    SDL_FillRect( qinfo->contents, 0, 0x0 );

    DEST( qinfo->contents,
          6 + ( ( hex_w - unit->prop.icon_w ) >> 1 ), ( ( qinfo->contents->h - unit->prop.icon_h ) >> 1 ),
          unit->prop.icon_w, unit->prop.icon_h );
    SOURCE( unit->prop.icon, 0, 0 );
    blit_surf();
    DEST( qinfo->contents,
          6 + ( ( hex_w - unit_info_icons->str_w ) >> 1 ),
          ( ( qinfo->contents->h - unit->prop.icon_h ) >> 1 ) + unit->prop.icon_h,
          unit_info_icons->str_w, unit_info_icons->str_h );
    SOURCE( unit_info_icons->str, 0, ( unit->str + 14 ) * unit_info_icons->str_h )
    blit_surf();

    DEST( qinfo->contents, 6, 6, nation_flag_width, nation_flag_height );
    SOURCE( nation_flags, 0, unit->nation->flag_offset );
    blit_surf();

    gui->font_std->align = ALIGN_X_LEFT | ALIGN_Y_TOP;
    write_text( gui->font_std, qinfo->contents, 12 + hex_w, 10, unit->name, 255 );
    write_text( gui->font_std, qinfo->contents, 12 + hex_w, 22, unit->prop.name, 255 );

    gui->font_status->align = ALIGN_X_LEFT | ALIGN_Y_TOP;
    if ( cur_player && !player_is_ally( unit->player, cur_player ) )
        len = sprintf( str, GS_AMMO "? " GS_FUEL "? " GS_ENTR "%i  " GS_NOEXP GS_NOEXP GS_NOEXP GS_NOEXP GS_NOEXP " ", unit->entr );
    else
        if ( unit_check_fuel_usage( unit ) )
            len = sprintf( str, GS_AMMO "%i " GS_FUEL "%i " GS_ENTR "%i  " GS_NOEXP GS_NOEXP GS_NOEXP GS_NOEXP GS_NOEXP " ", unit->cur_ammo, unit->cur_fuel, unit->entr );
        else
            len = sprintf( str, GS_AMMO "%i " GS_FUEL "- " GS_ENTR "%i  " GS_NOEXP GS_NOEXP GS_NOEXP GS_NOEXP GS_NOEXP " ", unit->cur_ammo, unit->entr );
    for ( i = 0; i < unit->exp_level; i++ )
        str[len - 6 + i] = (char)CharExp;
    str[len - 6 + i] = (char)(CharExpGrowth + (unit->exp % 100 / 20));
    write_text( gui->font_status, qinfo->contents, 12 + hex_w, 36, str, 255 );

    frame_apply( qinfo );
    frame_hide( qinfo, 0 );
}
