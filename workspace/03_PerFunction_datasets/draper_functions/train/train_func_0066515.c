gli_move_selection(int x, int y)
{
    int tx, ty;

    if (abs(x - last_x) < 5 && abs(y - last_y) < 5)
        return;

    if (!gli_mask || !gli_mask->hor || !gli_mask->ver)
    {
        gli_strict_warning("move_selection: mask not initialized");
        return;
    }

    tx = x < gli_mask->hor ? x : gli_mask->hor;
    ty = y < gli_mask->ver ? y : gli_mask->ver;

    gli_mask->select.x1 = last_x = tx;
    gli_mask->select.y1 = last_y = ty;

    gli_claimselect = FALSE;
    gli_windows_redraw();
    return;
}
