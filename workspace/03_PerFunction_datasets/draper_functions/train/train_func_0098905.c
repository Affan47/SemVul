xbaeGetCell(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    String value;

    if (row >= mw->matrix.rows || row < 0 ||
        column > mw->matrix.columns - 1 || column < 0)
    {
        XtAppWarningMsg(
            XtWidgetToApplicationContext((Widget) mw),
            "getCell", "badIndex", "XbaeMatrix",
            "XbaeMatrix: Row or column out of bounds for GetCell.",
            NULL, 0);
        return (NULL);
    }
    if (mw->matrix.draw_cell_callback)
    {
        Pixel bgcolor, fgcolor;
        Pixmap pixmap, mask;
        int width, height, depth;

        if (xbaeGetDrawCellValue(mw, row, column, &value, &pixmap,
                                 &mask, &width, &height, &bgcolor, &fgcolor,
                                 &depth) == XbaePixmap)
            value = "";
    }
    else if (!mw->matrix.cells)
        return "";
    else
        value = mw->matrix.cells[row][column];

    return value;
}
