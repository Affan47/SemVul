_gth_browser_hide_infobar (GthBrowser *browser)
{
	if (gtk_widget_get_visible (browser->priv->infobar))
		gtk_info_bar_response (GTK_INFO_BAR (browser->priv->infobar), GTK_RESPONSE_CLOSE);
}
