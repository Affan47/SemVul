HSBCallback(Widget scrollbar, XtPointer client_data,
                           XtPointer call_data)
#else
static void HSBCallback(scrollbar, client_data, call_data)
Widget scrollbar;
XtPointer client_data;
XtPointer call_data;
#endif
{
   ListTreeWidget w = (ListTreeWidget) client_data;
   XmScrollBarCallbackStruct *cbs = (XmScrollBarCallbackStruct *)call_data;

   w->list.hsbPos=cbs->value;
   HSB2X(w);

   LT_DBG(DARG,"XOffset=%d prefWidth=%d viewWidth=%d\n",
      w->list.XOffset,w->list.preferredWidth,w->list.viewWidth);
   if (w->list.XOffset!=w->list.lastXOffset) {
      DrawAll(w);
   }
}
