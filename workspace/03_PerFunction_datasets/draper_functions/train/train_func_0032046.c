XbaeMatrixRefreshCell(w, row, column)
Widget w;
int row;
int column;
{
    XbaeMatrixWidget mw = (XbaeMatrixWidget)w;

    if (!XtIsSubclass(w, xbaeMatrixWidgetClass))
        return;

    if (xbaeIsCellVisible(mw, row, column))
    {


        xbaeDrawCell(mw, row, column);
    }
}
