mg_detach_tab_cb(GtkWidget *item, chan * ch) {
	if (chan_get_tag(ch) == TAG_IRC) {

		mg_link_irctab(chan_get_userdata(ch), 1);
		return;
	}
#warning "xchat->ekg2, removed support for generic tabs"
}
