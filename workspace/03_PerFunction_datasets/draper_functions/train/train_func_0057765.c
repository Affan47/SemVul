editor_update_extra_bricks()
{
    int i, j;
    for ( i = 0; i < EDIT_WIDTH; i++ )
        for ( j = 0; j < EDIT_HEIGHT; j++ )
            if ( edit_cur_level->extras[i][j] != EX_NONE )
                editor_draw_brick( i, j );
    stk_display_update( STK_UPDATE_RECTS );
}
