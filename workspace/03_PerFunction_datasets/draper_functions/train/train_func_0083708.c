getConversionContext(w)
Widget	w;
{
    ConversionContext *context;

    if (XFindContext(XtDisplay(w), XtWindow(w),
		     convertPrivContext, (caddr_t *)&context)) {

	return NULL;
    } else {
	return context;
    }
}
