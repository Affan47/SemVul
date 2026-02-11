jumpProc (Widget bar, PanScrollRec *data, float *fraction)
{
  float	   	thumbSize, scaleFrac;
  int	 	previous;

  if (data->range == 0 || data->shown > data->range)
    return;

  XtVaGetValues(bar, XtNshown, &thumbSize, NULL);


  scaleFrac = (*fraction - (thumbSize/2)) / (1.0 - thumbSize);
  scaleFrac = Max(scaleFrac, 0.0);
  scaleFrac = Min(scaleFrac, 1.0);
  previous = data->position;
  data->position = (int)(scaleFrac * (data->range - data->shown));
  recalculateBar(data);


  if (data->position != previous)
    XtCallCallbackList(XtParent(bar), data->callback, (XtPointer)(ptrdiff_t)data->position);
}
