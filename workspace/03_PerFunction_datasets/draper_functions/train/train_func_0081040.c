next_command(Widget w, XEvent *e,
			 String *params, Cardinal *num_params)
#else
static void next_command(w, e, params, num_params)
Widget w;
XEvent *e;
String *params;
Cardinal *num_params;
#endif
{
    char *new;

    new = NextHistoryItem((XmtCliWidget)w);
    if (new != NULL) new_command(w,new);
}
