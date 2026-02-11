xbaeProcessDragACT(w, event, params, nparams)
Widget w;
XEvent *event;
String *params;
Cardinal *nparams;
{
#if XmVersion > 1001
    XbaeMatrixWidget mw;
    int x, y;
    int row, column;
    CellType cell;
    XbaeMatrixProcessDragCallbackStruct call_data;


    if (XtIsSubclass(w, xbaeMatrixWidgetClass))
        mw = (XbaeMatrixWidget)w;
    else if (XtIsSubclass(XtParent(w), xbaeMatrixWidgetClass))
        mw = (XbaeMatrixWidget)XtParent(w);
    else {
        XtAppWarningMsg(
            XtWidgetToApplicationContext(w),
            "processDragACT", "badWidget", "XbaeMatrix",
            "XbaeMatrix: Bad widget passed to ProcessDrag action",
            NULL, 0);
        return;
    }

    if (!mw->matrix.process_drag_callback)
        return;

    if (!xbaeEventToXY(mw, event, &x, &y, &cell))
        return;

    if (!xbaeXYToRowCol(mw, &x, &y, &row, &column, cell))
        return;

    call_data.reason = XbaeProcessDragReason;
    call_data.event = event;
    call_data.row = row;
    call_data.column = column;

    if (mw->matrix.draw_cell_callback)
    {
        Pixel bgcolor, fgcolor;
        int width, height, depth;

        call_data.type = xbaeGetDrawCellValue(
            mw, row, column, &call_data.string, &call_data.pixmap,
            &call_data.mask, &width, &height, &bgcolor, &fgcolor, &depth);
    }
    else
        call_data.string = mw->matrix.cells ?
            mw->matrix.cells[row][column] : "";

    call_data.num_params = *nparams;
    call_data.params = params;

    XtCallCallbackList((Widget)mw, mw->matrix.process_drag_callback,
                       (XtPointer)&call_data);
#endif
}
