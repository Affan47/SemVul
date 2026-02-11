enc_toggle_callback(Widget gw,
				XtPointer client_data,
				XtPointer call_data)
{
    PostContext		*context = (PostContext *)client_data;
    PostWidgets		*w = context->widgets;
    int			sel = ScrListGetFirstSelected(w->list);
    PostAttachment	*pa;
    char		msg[256];
    int			ok, enc;

    if (context->busy || sel < 0)
	return;

    if (gw == w->none_toggle)
	enc = MimeEncNone;
    else if (gw == w->base64_toggle)
	enc = MimeEncBase64;
    else if (gw == w->uue_toggle)
	enc = MimeEncUue;
    else if (gw == w->qp_toggle)
	enc = MimeEncQP;
    else {
	XBell(display, 0);
	return;
    }

    pa = context->attachments[sel];
    ok = attach_set_enc(pa, enc, msg);
    post_set_message(context, msg, !ok);
    if (ok) {
	print_attach_info(pa, msg);
	ScrListSetLine(w->list, sel, msg, None);
    }
    set_enc_toggles(w, pa);
}
