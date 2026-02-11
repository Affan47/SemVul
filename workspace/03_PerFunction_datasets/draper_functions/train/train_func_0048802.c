gli_start_selection(int x, int y)
{
    int tx, ty;

    if (!gli_mask || !gli_mask->hor || !gli_mask->ver)
    {
        gli_strict_warning("start_selection: mask not initialized");
        return;
    }

    tx = x < gli_mask->hor ? x : gli_mask->hor;
    ty = y < gli_mask->ver ? y : gli_mask->ver;

    gli_mask->select.x0 = last_x = tx;
    gli_mask->select.y0 = last_y = ty;
    gli_mask->select.x1 = 0;
    gli_mask->select.y1 = 0;

    gli_claimselect = FALSE;
    gli_force_redraw = 1;
    gli_windows_redraw();
    return;
}
