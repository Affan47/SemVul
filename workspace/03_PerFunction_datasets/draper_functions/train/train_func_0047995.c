xbaeDrawRowLabel(XbaeMatrixWidget mw, int row, Boolean pressed)
#else
xbaeDrawRowLabel(mw, row, pressed)
XbaeMatrixWidget mw;
int row;
Boolean pressed;
#endif
{
    int y;
    GC gc;
    Window win = XtWindow(mw);
    Boolean clipped = (row >= (int)mw->matrix.fixed_rows &&
                       row < TRAILING_VERT_ORIGIN(mw));

    Boolean button = mw->matrix.button_labels ||
        (mw->matrix.row_button_labels && mw->matrix.row_button_labels[row]);

    if (mw->matrix.row_labels[row][0] == '\0' && !button)
        return;


    if (row < (int)mw->matrix.fixed_rows)
        y = ROW_LABEL_OFFSET(mw) + ROW_HEIGHT(mw) * row + TEXT_Y_OFFSET(mw);
    else if (row >= TRAILING_VERT_ORIGIN(mw))
        y = TRAILING_FIXED_ROW_LABEL_OFFSET(mw) +
            ROW_HEIGHT(mw) * (row - TRAILING_VERT_ORIGIN(mw)) +
            TEXT_Y_OFFSET(mw);
    else
        y = ROW_LABEL_OFFSET(mw) + ROW_HEIGHT(mw) * (row - VERT_ORIGIN(mw)) +
            LABEL_Y_OFFSET(mw) - mw->matrix.first_row_offset;

    if (clipped)
        gc = mw->matrix.label_clip_gc;
    else
        gc = mw->matrix.label_gc;

    if (button)
    {
        XSetForeground(XtDisplay(mw), gc, mw->matrix.button_label_background);
        XFillRectangle(XtDisplay(mw), win, gc, VERT_SB_OFFSET(mw),
                       y - TEXT_Y_OFFSET(mw), ROW_LABEL_WIDTH(mw),
                       ROW_HEIGHT(mw));
    }

    XSetForeground(XtDisplay(mw), gc, mw->matrix.row_label_color);
    XSetBackground(XtDisplay(mw), gc, mw->matrix.button_label_background);

    if (mw->matrix.row_labels[row][0] != '\0')
        xbaeDrawString(mw, win, gc,
                       mw->matrix.row_labels[row],
                       strlen(mw->matrix.row_labels[row]),
                       TEXT_X_OFFSET(mw) + VERT_SB_OFFSET(mw), y,
                       mw->matrix.row_label_width,
                       mw->matrix.row_label_alignment, False,
                       mw->matrix.bold_labels, True, False,
                       mw->matrix.row_label_color);

    if (button)
        xbaeDrawCellShadow(mw, win, row, -1, VERT_SB_OFFSET(mw),
                           y - TEXT_Y_OFFSET(mw), ROW_LABEL_WIDTH(mw),
                           ROW_HEIGHT(mw), True, clipped, pressed);
}
