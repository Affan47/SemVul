CursorMovement (Widget	w,
			    XEvent *	event,
			    String *	params __attribute__((unused)),
			    Cardinal *	nparams __attribute__((unused)))
{
  TextViewData * data;
  char	    msg[256];
  XPoint    index;
  GridPoint grid;

  data = XtCanvasData(w);

  index.x = XIndex(event->xmotion.x);
  index.y = YIndex(event->xmotion.y);
  GetGridCoords(data->grid, &index, &grid);

  if (grid.x != cellUnderMouse.coord.x || grid.y != cellUnderMouse.coord.y) {
    lowlightCell(w, &cellUnderMouse);

    cellUnderMouse.coord = grid;
    cellUnderMouse.index = index;
    cellUnderMouse.bounds.x = (index.x * data->cellWidth) - data->xOffset;
    cellUnderMouse.bounds.y = (index.y * data->cellHeight) - data->yOffset;
    cellUnderMouse.bounds.width = data->cellWidth;
    cellUnderMouse.bounds.height = data->cellHeight;
    highlightCell(w, data, &cellUnderMouse);
    sprintf(msg, "%7.3f, %7.3f", grid.x, grid.y);
    setMessageLine(msg);
  }
}
