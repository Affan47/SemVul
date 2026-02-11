draw_bb(int color)
{
    if (ED4_ROOT->get_device()) {
        ED4_ROOT->get_device()->push_clip_scale();
        if (adjust_clipping_rectangle()) {
            AW_pos x1, y1;
            calc_world_coords( &x1, &y1 );
            ED4_ROOT->world_to_win_coords(ED4_ROOT->get_aww(), &x1, &y1);
            ED4_ROOT->get_device()->box(color, false, x1, y1, extension.size[WIDTH]-1, extension.size[HEIGHT]-1, (AW_bitset)-1, 0, 0);
        }
        ED4_ROOT->get_device()->pop_clip_scale();
    }
}
