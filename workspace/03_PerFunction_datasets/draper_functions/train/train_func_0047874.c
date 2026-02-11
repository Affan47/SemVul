xbaeDrawCell(mw, row, column)
XbaeMatrixWidget mw;
int row, column;
{
    Pixel bg, fg;
    String string;
    int x, y;

    if (mw->matrix.disable_redisplay || mw->matrix.rows == 0 ||
        mw->matrix.columns == 0)
        return;


    xbaeRowColToXY(mw, row, column, &x, &y);

    xbaeComputeCellColors(mw, row, column, &fg, &bg);

#if CELL_WIDGETS
    if (mw->matrix.cell_widgets[row][column])
        xbaeDrawCellWidget(mw, row, column, x, y,
                           mw->matrix.cell_widgets[row][column], bg, fg);
    else
#endif

        if (!mw->matrix.draw_cell_callback)
        {
            if (row < mw->matrix.rows && column < mw->matrix.columns)
            {
                if (mw->matrix.cells && mw->matrix.cells[row])
                    string = mw->matrix.cells[row][column];
                else
                    string = "";

                xbaeDrawCellString(mw, row, column, x, y, string, bg, fg);
            }
        }
        else
        {
            Pixmap pixmap;
            Pixmap mask;
            XbaeCellType type;
            int width, height;
            int depth;

            if (row < mw->matrix.rows && column < mw->matrix.columns)
            {
                type = xbaeGetDrawCellValue(mw, row, column, &string, &pixmap,
                                            &mask, &width, &height, &bg, &fg,
                                            &depth);
                if (type == XbaeString)
                    xbaeDrawCellString(mw, row, column, x, y, string, bg, fg);
                else if (type == XbaePixmap)
                    xbaeDrawCellPixmap(mw, row, column, x, y, pixmap, mask,
                                       width, height, bg, fg, depth);
            }
        }
}
