do_request (UIRequest* req)
{
	if (req->type == ErrorMessage) {

		process_error_message (req->chn, req->msg);
		free (const_cast<char*>(req->msg));
		req->msg = 0;

	} else if (req->type == Quit) {

		do_quit ();

	} else if (req->type == CallSlot) {

		req->slot ();

	} else if (req->type == TouchDisplay) {

		req->display->touch ();
		if (req->display->delete_after_touch()) {
			delete req->display;
		}

	} else if (req->type == StateChange) {

		req->widget->set_state (req->new_state);

	} else if (req->type == SetTip) {

#ifdef GTK_NEW_TOOLTIP_API


		gtk_widget_set_tooltip_text (req->widget->gobj(), req->msg);
#else
		tips->set_tip (*req->widget, req->msg, "");
#endif

	} else {

		error << "GtkUI: unknown request type "
		      << (int) req->type
		      << endmsg;
	}
}
