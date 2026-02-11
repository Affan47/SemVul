scrollProc (Widget bar, PanScrollRec *data, int position)
{
  int	    distance;
  Position  previous;

  previous = data->position;

  if (data->orientation == XtorientHorizontal)
    position = - position;

  if (data->scroll_step != 0)
    distance = data->scroll_step;
  else
    distance = Max(0.9 * data->shown, 4);
  if (position < 0)
    data->position -= distance;
  else
    data->position += distance;
  recalculateBar(data);


  if (data->position != previous)
    XtCallCallbackList(XtParent(bar), data->callback, (XtPointer)(ptrdiff_t)data->position);
}
