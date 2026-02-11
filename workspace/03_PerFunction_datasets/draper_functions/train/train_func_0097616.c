XtCompositeChildren (widget, number)
     Widget widget;
     unsigned int* number;
{
  CompositeWidget cw = (CompositeWidget)widget;
  Widget* result;
  int n;
  int i;

  if (!XtIsComposite (widget))
    {
      *number = 0;
      return NULL;
    }
  n = cw->composite.num_children;
  result = (Widget*)XtMalloc (n * sizeof (Widget));
  *number = n;
  for (i = 0; i < n; i++)
    result [i] = cw->composite.children [i];
  return result;
}
