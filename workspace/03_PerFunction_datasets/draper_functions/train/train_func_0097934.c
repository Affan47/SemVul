load_commit_cb(WebKitWebView* page, WebKitWebFrame* frame, gpointer data) {
    const gchar* uri = webkit_web_frame_get_uri(frame);
    if (uri)
        gtk_entry_set_text(GTK_ENTRY (browser->uri_entry), uri);
}
