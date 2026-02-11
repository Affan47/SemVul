statusStartCallback(w, client_data, call_data)
Widget w;
XtPointer client_data;
XtPointer call_data;
{
    IMIC *icp = (IMIC *)client_data;

    TRACE(("statusStartCallback(icp=0x%lx)\n", icp));

    if (!(icp->common_attr.input_style & XIMStatusCallbacks))
	return;

    statusStart(icp);
}
