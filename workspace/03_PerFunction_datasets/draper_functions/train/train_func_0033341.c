call_suspend_hook(ScrollableWidget w)
{
    ScrollableWidgetClass	class = (ScrollableWidgetClass)XtClass(w);

    if (class->scrollable_class.suspend_hook)
	class->scrollable_class.suspend_hook(w);
}
