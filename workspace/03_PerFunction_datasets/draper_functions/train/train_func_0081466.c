xbaeSelectColumn(mw, column)
XbaeMatrixWidget mw;
int column;
{
    int i, tr, br;
    Boolean once = False;

    unsigned int clip_reason = CLIP_NONE;

    if (column >= mw->matrix.columns || column < 0)
    {
        XtAppWarningMsg(
            XtWidgetToApplicationContext((Widget) mw),
            "selectColumn", "badIndex", "XbaeMatrix",
            "XbaeMatrix: Column out of bounds for SelectColumn.",
            NULL, 0);
        return;
    }


    if (!mw->matrix.selected_cells)
        xbaeCopySelectedCells(mw);


    if (mw->matrix.scroll_select)
        xbaeMakeColumnVisible(mw, column);


    if (!mw->matrix.scroll_select && !xbaeIsColumnVisible(mw, column))
    {
        for (i = 0; i < mw->matrix.rows; i++)
            if (!mw->matrix.selected_cells[i][column])
            {
                mw->matrix.num_selected_cells++;
                mw->matrix.selected_cells[i][column] = True;
            }
        return;
    }


    if (column < (int)mw->matrix.fixed_columns)
        clip_reason = CLIP_FIXED_COLUMNS;
    else if (column >= TRAILING_HORIZ_ORIGIN(mw))
        clip_reason = CLIP_TRAILING_FIXED_COLUMNS;
    if (CLIP_NONE != clip_reason)
        xbaeSetClipMask(mw, clip_reason | CLIP_VISIBLE_HEIGHT);


    xbaeGetVisibleRows(mw, &tr, &br);
    for (i = 0; i < mw->matrix.rows; i++)
    {
        if (!mw->matrix.selected_cells[i][column])
        {
            mw->matrix.selected_cells[i][column] = True;
            mw->matrix.num_selected_cells++;
            if ((i >= tr && i <= br) ||
                (i < (int)mw->matrix.fixed_rows) ||
                (i >= TRAILING_VERT_ORIGIN(mw)))
            {
                if ((! once) && (i >= TRAILING_VERT_ORIGIN(mw)))
                {
                    once = True;
                    xbaeSetClipMask(mw, clip_reason | CLIP_TRAILING_FIXED_ROWS);
                }

                xbaeClearCell(mw, i, column);
                xbaeDrawCell(mw, i, column);
            }
        }
    }

    if (once || (CLIP_NONE != clip_reason))
        xbaeSetClipMask(mw, CLIP_NONE);
}
