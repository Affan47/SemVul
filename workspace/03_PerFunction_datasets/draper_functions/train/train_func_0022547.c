scrollVertical (Widget	w __attribute__((unused)),
	XtPointer	client_data,
	XtPointer	call_data)
{
  Widget    canvas;
  Dimension width, height;
  int       previous, distance;
  char	    msg[256];
  XPoint    index1, index2;
  GridPoint grid1, grid2;

  TextViewData *data = client_data;
  int		y = (int)call_data;

  canvas = data->canvas;
  width  = XtWidth(canvas);
  height = XtHeight(canvas);

  previous = data->yOffset;
  distance = abs(y - previous);
  data->yOffset = y;

  if (distance >= height) {

    XClearWindow(XtDisplay(canvas), XtWindow(canvas));
    redrawValues(canvas, 0, 0, width, height);
  } else if (y < previous) {

    distance = previous - y;
    XCopyArea(XtDisplay(canvas),
    		XtWindow(canvas), XtWindow(canvas), data->scrollGC,
		0, 0, width, height - distance, 0, distance);
    redrawValues(canvas, 0, 0, width, distance);
  } else if (y > previous) {

    distance = y - previous;
    XCopyArea(XtDisplay(canvas),
    		XtWindow(canvas), XtWindow(canvas), data->scrollGC,
		0, distance, width, height - distance, 0, 0);
    redrawValues(canvas, 0, height - distance, width, distance);
  }
  data->yOffset = y;


  index1.y = YIndex(height); index1.x = 0;
  GetGridCoords(data->grid, &index1, &grid1);
  index2.y = YIndex(0); index2.x = 0;
  GetGridCoords(data->grid, &index2, &grid2);
  sprintf(msg, "%7.3f to %7.3f", grid1.y, grid2.y);
  setMessageLine(msg);
}
