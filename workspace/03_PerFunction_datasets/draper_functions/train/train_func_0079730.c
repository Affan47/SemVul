visitSelection(TextSelectionVisitor *visitor,
			       PDFRectangle *selection,
			       SelectionStyle style) {
  TextLine *p, *begin, *end;
  PDFRectangle child_selection;
  double start_x, start_y, stop_x, stop_y;

  begin = NULL;
  end = NULL;
  start_x = selection->x1;
  start_y = selection->y1;
  stop_x = selection->x2;
  stop_y = selection->y2;

  for (p = lines; p != NULL; p = p->next) {
    if (selection->x1 < p->xMax && selection->y1 < p->yMax &&
	selection->x2 < p->xMax && selection->y2 < p->yMax && begin == NULL) {
      begin = p;
      if (selection->x1 < selection->x2) {
	start_x = selection->x1;
	start_y = selection->y1;
	stop_x = selection->x2;
	stop_y = selection->y2;
      } else {
	start_x = selection->x2;
	start_y = selection->y2;
	stop_x = selection->x1;
	stop_y = selection->y1;
      }
    } else if (selection->x1 < p->xMax && selection->y1 < p->yMax && begin == NULL) {
      begin = p;
      start_x = selection->x1;
      start_y = selection->y1;
      stop_x = selection->x2;
      stop_y = selection->y2;
    } else if (selection->x2 < p->xMax && selection->y2 < p->yMax && begin == NULL) {
      begin = p;
      start_x = selection->x2;
      start_y = selection->y2;
      stop_x = selection->x1;
      stop_y = selection->y1;
    }

    if (((selection->x1 > p->xMin && selection->y1 > p->yMin) ||
	 (selection->x2 > p->xMin && selection->y2 > p->yMin))
	&& (begin != NULL))
      end = p->next;
  }


  if (end == begin)
    return;

  visitor->visitBlock (this, begin, end, selection);

  for (p = begin; p != end; p = p->next) {
    if (p == begin && style != selectionStyleLine) {
      child_selection.x1 = start_x;
      child_selection.y1 = start_y;
    } else {
      child_selection.x1 = 0;
      child_selection.y1 = 0;
    }
    if (p->next == end && style != selectionStyleLine) {
      child_selection.x2 = stop_x;
      child_selection.y2 = stop_y;
    } else {
      child_selection.x2 = page->pageWidth;
      child_selection.y2 = page->pageHeight;
    }

    p->visitSelection(visitor, &child_selection, style);
  }
}
