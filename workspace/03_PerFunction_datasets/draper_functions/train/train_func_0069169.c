move_or_rotate(guint state, gfloat x, gfloat y, gfloat angle)
{
    guint what = REFRESH_IMAGE | APPEND_HISTORY;

    if (state & GDK_CONTROL_MASK) {
        matrix_rotate(angle);
        what |= REFRESH_STATUS;
    } else
        matrix_move(x, y);

    refresh(what);
}
