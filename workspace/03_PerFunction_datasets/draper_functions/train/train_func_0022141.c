pixel2pos(AW_pos click_x) {


    int       length_of_char = font_group.get_width(ED4_G_SEQUENCES);
    ED4_index scr_pos        = int((click_x-CHARACTEROFFSET) / length_of_char);
    int       max_scrpos     = root_group_man->remap()->get_max_screen_pos();

    if (scr_pos>max_scrpos) scr_pos = max_scrpos;

    return scr_pos;
}
