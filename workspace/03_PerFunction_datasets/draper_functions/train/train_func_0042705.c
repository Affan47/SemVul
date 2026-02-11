rectangle_select_button_press(gpaint_tool * tool, int x, int y)
{
    gpaint_rectangle_select *rs = GPAINT_RECTANGLE_SELECT(tool);
    debug_fn();

    if (drawing_in_bounds(tool->drawing, x, y))
    {
        set_point(&rs->v1, x, y);
        set_point(&rs->v2, x, y);
        select_rectangle(rs->selection, &rs->v1, &rs->v2);
    }
}
