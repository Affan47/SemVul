IMOpenIM (Display *display, ...)
{
    va_list var;
    int total_count;
    XIMArg *args;
    XIMS ims;
    char *modifiers;
    Status ret;

    Va_start (var, display);
    _IMCountVaList (var, &total_count);
    va_end (var);

    Va_start (var, display);
    _IMVaToNestedList (var, total_count, &args);
    va_end (var);

    modifiers = _FindModifiers (args);

    ims = _GetIMS (modifiers);
    if (ims == (XIMS) NULL)
        return (XIMS) NULL;


    ims->core.display = display;

    ims->protocol = (*ims->methods->setup) (display, args);
    XFree (args);
    if (ims->protocol == (void *) NULL)
    {
	XFree (ims);
	return (XIMS) NULL;
    }

    ret = (ims->methods->openIM) (ims);
    if (ret == False)
    {
	XFree (ims);
	return (XIMS) NULL;
    }

    return (XIMS) ims;
}
