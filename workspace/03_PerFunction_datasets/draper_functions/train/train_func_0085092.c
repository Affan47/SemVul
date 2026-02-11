engine_show_game_menu( int cx, int cy )
{
    int i;
    if ( setup.type == SETUP_RUN_TITLE ) {
        status = STATUS_TITLE_MENU;
        if ( cy + gui->main_menu->frame->img->img->h >= sdl.screen->h )
            cy = sdl.screen->h - gui->main_menu->frame->img->img->h;
        group_move( gui->main_menu, cx, cy );
        group_hide( gui->main_menu, 0 );
        group_set_active( gui->main_menu, ID_SAVE, 0 );
        group_set_active( gui->main_menu, ID_RESTART, 0 );
    }
    else {
        engine_check_menu_buttons();
        gui_show_menu( cx, cy );
        status = STATUS_GAME_MENU;
        group_set_active( gui->main_menu, ID_SAVE, 1 );
        group_set_active( gui->main_menu, ID_RESTART, 1 );
    }

    group_lock_button( gui->opt_menu, ID_C_SUPPLY, config.supply );
    group_lock_button( gui->opt_menu, ID_C_WEATHER, config.weather );
    group_lock_button( gui->opt_menu, ID_C_GRID, config.grid );
    group_lock_button( gui->opt_menu, ID_C_SHOW_CPU, config.show_cpu_turn );
    group_lock_button( gui->opt_menu, ID_C_SHOW_STRENGTH, config.show_bar );
    group_lock_button( gui->opt_menu, ID_C_SOUND, config.sound_on );

    gui_update_slot_tooltips();
    for ( i = 0; i < SLOT_COUNT; i++ )
        if ( slot_is_valid( i ) )
            group_set_active( gui->load_menu, ID_LOAD_0 + i, 1 );
        else
            group_set_active( gui->load_menu, ID_LOAD_0 + i, 0 );
}
