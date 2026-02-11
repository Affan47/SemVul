XbaeMatrixGetCellUserData(w, row, column)
Widget w;
int row;
int column;
{
    XbaeMatrixWidget mw;
    XtPointer data;

    if (!XtIsSubclass(w, xbaeMatrixWidgetClass))
        return NULL;

    mw = (XbaeMatrixWidget) w;
    if (mw->matrix.cell_user_data)
        data = mw->matrix.cell_user_data[row][column];
    else
        return NULL;

    return data;
}
