insert(Widget gw, XEvent *event,
		   String *params, Cardinal *no_params)
{
    TextFieldWidget	w = (TextFieldWidget)gw;
    char		buffer[16];
    String		param;
    Cardinal		n_params;
    KeySym		keysym;
    long		len;

    if (!event || (event->type != KeyPress && event->type != KeyRelease))
	return;

    len = XLookupString(&event->xkey, buffer, sizeof buffer, &keysym, NULL);
    if (len <= 0)
	return;
    buffer[len] = '\0';
    param = buffer;
    n_params = 1;

    insert_string((Widget)w, event, &param, &n_params);
}
