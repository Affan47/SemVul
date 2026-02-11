show_cursor_at(ED4_terminal *target_terminal, ED4_index scr_pos)
{
    if (owner_of_cursor) {
        if (is_partly_visible()) {
            delete_cursor(cursor_abs_x, owner_of_cursor);
        }

        owner_of_cursor->set_refresh();
        owner_of_cursor->parent->refresh_requested_by_child();
        owner_of_cursor = NULL;
        ED4_ROOT->refresh_window(0);
        DRAW = 1;
    }

    target_terminal->scroll_into_view(ED4_ROOT->get_aww());

    AW_pos termw_x, termw_y;
    target_terminal->calc_world_coords( &termw_x, &termw_y );

    screen_position = scr_pos;

    int length_of_char = ED4_ROOT->font_group.get_width(ED4_G_SEQUENCES);

    AW_pos world_x = termw_x + length_of_char*screen_position + CHARACTEROFFSET;
    AW_pos world_y = termw_y;

    AW_pos win_x = world_x;
    AW_pos win_y = world_y;
    ED4_ROOT->world_to_win_coords(ED4_ROOT->get_aww(), &win_x, &win_y);

    cursor_abs_x = (long int)world_x;
    owner_of_cursor = target_terminal;

    draw_cursor(win_x, win_y);

    GB_transaction gb_dummy(GLOBAL_gb_main);
    updateAwars();

    return ED4_R_OK;
}
