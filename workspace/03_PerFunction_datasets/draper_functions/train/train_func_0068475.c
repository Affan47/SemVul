Initialize(Widget request, Widget init,
		       ArgList arglist, Cardinal *num_args)
#else
static void Initialize(request, init, arglist, num_args)
Widget request;
Widget init;
ArgList arglist;
Cardinal *num_args;
#endif
{
    XmtInputFieldWidget iw = (XmtInputFieldWidget) init;


    if (iw->input_field.buffer_symbol_name)
	iw->input_field.buffer_symbol_name =
	    XtNewString(iw->input_field.buffer_symbol_name);
    BindBufferSymbol(iw);
    if (iw->input_field.target_symbol_name)
	iw->input_field.target_symbol_name =
	    XtNewString(iw->input_field.target_symbol_name);
    BindTargetSymbol(iw);


    if (iw->input_field.input) {
	iw->input_field.input = XtNewString(iw->input_field.input);
	(void)SetValueOnSymbols(iw, iw->input_field.input, False);
    }
    else if (iw->input_field.buffer_symbol)
	SetValueFromSymbol(iw);


    if (iw->input_field.pattern)
	iw->input_field.pattern_length = strlen(iw->input_field.pattern);
    else
	iw->input_field.pattern_length = 0;


    if (iw->text.max_length != MAXINT)
	iw->input_field.max_length = iw->text.max_length;
    else if (iw->input_field.pattern)
	iw->input_field.max_length = iw->input_field.pattern_length;
    else if (iw->input_field.buffer_symbol)
	iw->input_field.max_length =
	    XmtSymbolSize(iw->input_field.buffer_symbol);
    else
	iw->input_field.max_length = MAXINT;

    XmTextSetMaxLength(init, iw->input_field.overstrike?MAXINT:
		       iw->input_field.max_length);


    if (!iw->core.sensitive || !iw->core.ancestor_sensitive)
	XtVaSetValues(init, XmtNlayoutSensitive, False, NULL);


    if (iw->input_field.input)
	SetString(init, iw->input_field.input);

    XtAddCallback(init, XmNactivateCallback, Activate, NULL);
    XtAddCallback(init, XmNlosingFocusCallback, Activate, NULL);
    XtAddCallback(init, XmNvalueChangedCallback, ValueChanged, NULL);


    if (iw->input_field.overstrike)
	XtAddCallback(init, XmNmodifyVerifyCallback, HandleOverstrike, NULL);


    if (iw->input_field.pattern) {
	XtAddCallback(init, XmNmodifyVerifyCallback, HandlePattern, NULL);
    }


    iw->input_field.input_changed = False;
    iw->input_field.pattern_skip = 0;
    iw->input_field.error_state = False;
    iw->input_field.ignore_symbol_notify = False;
}
