XbaeMatrixGetNumSelected(w)
Widget w;
{
    XbaeMatrixWidget mw;

    if (!XtIsSubclass(w, xbaeMatrixWidgetClass))
        return 0;

    mw = (XbaeMatrixWidget) w;

    return mw->matrix.selected_cells ? mw->matrix.num_selected_cells : 0;
}
