visitSelection(TextSelectionVisitor *visitor,
			      PDFRectangle *selection,
			      SelectionStyle style)
{
  int i, begin, end;
  double mid;

  begin = len;
  end = 0;
  for (i = 0; i < len; i++) {
    mid = (edge[i] + edge[i + 1]) / 2;
    if (selection->x1 < mid || selection->x2 < mid)
      if (i < begin)
	begin = i;
    if (mid < selection->x1 || mid < selection->x2)
      end = i + 1;
  }


  if (end <= begin)
    return;

  visitor->visitWord (this, begin, end, selection);
}
