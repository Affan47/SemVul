contact_update_status(struct contact *ec)
{
	eb_account *ea = NULL;
	LList *l;


	for (l = ec->accounts; l; l = l->next) {
		eb_account *account = l->data;

		if (account->online) {
			if (account->service_id == ec->default_chatb) {
				ea = account;
				break;
			} else if (!ea || !ea->online)
				ea = account;
		} else if (!ea && account->service_id == ec->default_chatb)
			ea = account;
	}

	if (!ea)
		return;

	ec->status = ea->status;
	ec->label = ec->nick;


	if (ec->icon_handler == -1) {
		if (RUN_SERVICE(ea)->get_status_pixbuf)
			ec->pix = RUN_SERVICE(ea)->get_status_pixbuf(ea);
		else if (RUN_SERVICE(ea)->get_status_pixmap) {
			GdkPixbuf *tmp = gdk_pixbuf_new_from_xpm_data(
				(const char **)RUN_SERVICE(ea)->
				get_status_pixmap(ea));
			ec->pix = tmp;
		} else
			ec->pix = iconblank_pb;

		gtk_tree_store_set(contact_list_store, ec->list_item,
			MAIN_VIEW_ICON, ec->pix,
			MAIN_VIEW_LABEL, ec->label,
			MAIN_VIEW_STATUS, ec->status,
			MAIN_VIEW_STATUS_TIP, ea->tiptext, -1);
	} else
		gtk_tree_store_set(contact_list_store, ec->list_item,
			MAIN_VIEW_LABEL, ec->label,
			MAIN_VIEW_STATUS, ec->status,
			MAIN_VIEW_STATUS_TIP, ea->tiptext, -1);

	if (!iGetLocalPref("do_noautoresize")) {
		int width = contact_list->allocation.width;
		int width2, height2;
		int width3, height3;

		if (GTK_WIDGET_VISIBLE(GTK_SCROLLED_WINDOW(contact_window)->
				vscrollbar)) {
			width3 = GTK_SCROLLED_WINDOW(contact_window)->
				vscrollbar->allocation.width;
			height3 =
				GTK_SCROLLED_WINDOW(contact_window)->
				vscrollbar->allocation.height;
		} else {
			width3 = 0;
			height3 = 0;
		}
		width2 = contact_window->allocation.width;
		height2 = contact_window->allocation.height;

		if (width + width3 > width2)
			gtk_widget_set_size_request(contact_window,
				width + width3 + 5, height2);
	}
}
