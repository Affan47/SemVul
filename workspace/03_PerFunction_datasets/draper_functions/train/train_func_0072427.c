reset_all_for_new_config()
{
    horizontal_fl = NULL;
    vertical_fl   = NULL;

    scrolled_rect.scroll_top    = NULL;
    scrolled_rect.scroll_bottom = NULL;
    scrolled_rect.scroll_left   = NULL;
    scrolled_rect.scroll_right  = NULL;

    scrolled_rect.world_x = 0;
    scrolled_rect.world_y = 0;
    scrolled_rect.width   = 0;
    scrolled_rect.height  = 0;

    slider_pos_horizontal = 0;
    slider_pos_vertical   = 0;

    coords.top_area_x      = 0;
    coords.top_area_y      = 0;
    coords.top_area_height = 0;

    coords.middle_area_x = 0;
    coords.middle_area_y = 0;

    coords.window_width  = 0;
    coords.window_height = 0;

    coords.window_upper_clip_point = 0;
    coords.window_lower_clip_point = 0;
    coords.window_left_clip_point  = 0;
    coords.window_right_clip_point = 0;

    ED4_ROOT->aw_root->awar(awar_path_for_cursor)->write_int(0);
    ED4_ROOT->aw_root->awar(awar_path_for_Ecoli)->write_int(0);
    ED4_ROOT->aw_root->awar(awar_path_for_basePos)->write_int(0);
    ED4_ROOT->aw_root->awar(awar_path_for_IUPAC)->write_string(ED4_IUPAC_EMPTY);
    ED4_ROOT->aw_root->awar(awar_path_for_helixNr)->write_string("");

    if (next) next->reset_all_for_new_config();
}
