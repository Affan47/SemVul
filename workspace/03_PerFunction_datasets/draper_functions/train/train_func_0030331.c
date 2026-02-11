web_view_update_document_highlights (EWebView *web_view)
{
	WebKitWebView *webkit_web_view;
	GList *head, *link;

	webkit_web_view = WEBKIT_WEB_VIEW (web_view);

	head = g_queue_peek_head_link (&web_view->priv->highlights);

	for (link = head; link != NULL; link = g_list_next (link))
		webkit_web_view_mark_text_matches (
			webkit_web_view, link->data, FALSE, 0);

	webkit_web_view_set_highlight_text_matches (webkit_web_view, TRUE);
}
