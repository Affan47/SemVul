gnc_html_set_urltype_cb( GncHtml* self, GncHTMLUrltypeCB urltype_cb )
{
    GncHtmlPrivate* priv;

    g_return_if_fail( self != NULL );
    g_return_if_fail( GNC_IS_HTML(self) );

    priv = GNC_HTML_GET_PRIVATE(self);
    priv->urltype_cb = urltype_cb;
}
