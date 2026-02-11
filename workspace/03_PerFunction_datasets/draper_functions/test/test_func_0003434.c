XbaeMatrixUnhighlightRow(w, row)
Widget w;
int row;
{
    XbaeMatrixWidget mw;
    int column, lc, rc;
    Boolean visible;
    unsigned char highlight;

    if (!XtIsSubclass(w, xbaeMatrixWidgetClass))
        return;
    mw = (XbaeMatrixWidget) w;

    if (row >= mw->matrix.rows || row < 0)
    {
        XtAppWarningMsg(
            XtWidgetToApplicationContext((Widget) mw),
            "highlightRow", "badIndex", "XbaeMatrix",
            "XbaeMatrix: Row out of bounds for UnhighlightRow.",
            NULL, 0);
        return;
    }

    if (!mw->matrix.highlighted_cells)
        return;

    mw->matrix.highlight_location = UnhighlightRow;

    visible = xbaeIsRowVisible(mw, row);


    xbaeGetVisibleColumns(mw, &lc, &rc);
    highlight = (IN_GRID_ROW_MODE(mw) ? HighlightRow : HighlightOther);
    for (column = 0; column < mw->matrix.columns; column++)
    {
        if (mw->matrix.highlighted_cells[row][column] & highlight)
        {
            if (visible)
                xbaeDrawCell(mw, row, column);
            mw->matrix.highlighted_cells[row][column] &= ~highlight;
        }
    }

    mw->matrix.highlight_location = HighlightNone;
}
