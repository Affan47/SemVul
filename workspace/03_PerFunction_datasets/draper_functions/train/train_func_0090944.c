file_sel_callback(Widget gw,
			      XtPointer client_data,
			      XtPointer call_data)
{
    PostContext 	*context = (PostContext *)client_data;
    PostWidgets		*w = context->widgets;
    char		*file_name = (char *)call_data;
    PostAttachment	*pa;
    char		buffer[256];

    if (!context->busy) {
	XBell(display, 0);
	return;
    }

    XtPopdown(w->file_sel);
    post_unset_busy(context);

    if (!file_name) {
	set_ready_message(context, False);
	return;
    }

    pa = create_attachment(file_name, buffer);
    post_set_message(context, buffer, !pa);
    if (pa) {
	int	n = ++context->n_attachments;

	context->attachments =
	    (PostAttachment **)XtRealloc((char *)context->attachments,
					 n * sizeof context->attachments[0]);
	context->attachments[n - 1] = pa;
	print_attach_info(pa, buffer);
	ScrListAddLine(w->list, buffer, None);
	Remanage(w->list_manager);
	ScrListSetSelected(w->list, n - 1, True);
	ScrListMakeVisible(w->list, n - 1);
	set_attach_widgets(w, pa);
    }
}
