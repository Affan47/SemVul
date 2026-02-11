web_view_load_status_changed_cb (WebKitWebView *webkit_web_view,
                                 GParamSpec *pspec,
                                 gpointer user_data)
{
	WebKitLoadStatus status;
	ESearchBar *search_bar;

	status = webkit_web_view_get_load_status (webkit_web_view);
	if (status != WEBKIT_LOAD_FINISHED)
		return;

	if (!user_data)
		return;

	search_bar = E_SEARCH_BAR (user_data);

	if (gtk_widget_get_visible (GTK_WIDGET (search_bar))) {
		if (search_bar->priv->active_search != NULL) {
		       search_bar_find (search_bar, TRUE);
		}
	} else {
		e_web_view_update_highlights (search_bar->priv->web_view);
	}
}
