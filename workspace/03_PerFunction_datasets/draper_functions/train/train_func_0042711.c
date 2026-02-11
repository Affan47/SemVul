lw_lucid_widget_p (widget)
     Widget widget;
{
  WidgetClass the_class = XtClass (widget);

  if (the_class == xlwMenuWidgetClass)
    return True;
  if (the_class == overrideShellWidgetClass)
    return (XtClass (((CompositeWidget)widget)->composite.children [0])
	    == xlwMenuWidgetClass);
  return False;
}
