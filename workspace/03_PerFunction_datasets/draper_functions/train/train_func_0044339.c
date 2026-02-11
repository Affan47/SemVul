setTextViewGrid (Widget	view, Grid *	grid)
{
  TextViewData * data;

  data = XtCanvasData(view);
  if (data->grid != NULL)
    DisposeGrid(data->grid);
  data->grid = grid;
  recalculateDisplayParameters(view);
  if (XtIsRealized(view))
    XClearArea(XtDisplay(view), XtWindow(view), 0, 0, 0, 0, True);
}
