engine_check_scroll(int by_wheel)
{
    int region;
    int tol = 3;
    int mx, my, cx, cy;
    if ( scroll_block ) return;
    if ( setup.type == SETUP_RUN_TITLE ) return;
    if( !by_wheel ) {

        scroll_hori = scroll_vert = SCROLL_NONE;
        if ( !scroll_block_keys ) {
            if ( event_check_key( SDLK_UP ) && map_y > 0)
                scroll_vert = SCROLL_UP;
            else
                if ( event_check_key( SDLK_DOWN ) && map_y < map_h - map_sh )
                    scroll_vert = SCROLL_DOWN;
            if ( event_check_key( SDLK_LEFT ) && map_x > 0 )
                scroll_hori = SCROLL_LEFT;
            else
                if ( event_check_key( SDLK_RIGHT ) && map_x < map_w - map_sw )
                    scroll_hori = SCROLL_RIGHT;
        }
        if ( scroll_vert == SCROLL_NONE && scroll_hori == SCROLL_NONE ) {

            event_get_cursor_pos( &mx, &my );
            if ( my <= tol && map_y > 0 )
                scroll_vert = SCROLL_UP;
            else
                if ( mx >= sdl.screen->w - tol - 1 && map_x < map_w - map_sw )
                    scroll_hori = SCROLL_RIGHT;
                else
                    if ( my >= sdl.screen->h - tol - 1 && map_y < map_h - map_sh )
                        scroll_vert = SCROLL_DOWN;
                    else
                        if ( mx <= tol && map_x > 0 )
                            scroll_hori = SCROLL_LEFT;
        }
    }

    if ( scroll_vert != SCROLL_NONE || scroll_hori != SCROLL_NONE ) {
        if ( scroll_vert == SCROLL_UP )
            engine_goto_xy( map_x, map_y - 2 );
        else
            if ( scroll_hori == SCROLL_RIGHT )
                engine_goto_xy( map_x + 2, map_y );
            else
                if ( scroll_vert == SCROLL_DOWN )
                    engine_goto_xy( map_x, map_y + 2 );
                else
                    if ( scroll_hori == SCROLL_LEFT )
                        engine_goto_xy( map_x - 2, map_y );
        event_get_cursor_pos( &cx, &cy );
        if(engine_get_map_pos( cx, cy, &mx, &my, &region ))
            engine_update_info( mx, my, region );
        if ( !by_wheel )
            scroll_block = 1;
    }
}
