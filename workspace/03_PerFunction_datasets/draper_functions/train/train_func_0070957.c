gdome_xpath_xpnsresolv_unref (GdomeXPathNSResolver *self, GdomeException *exc)
{
	Gdome_xpath_XPathNSResolver *priv = (Gdome_xpath_XPathNSResolver *)self;

	g_return_if_fail (self != NULL);
	g_return_if_fail (exc != NULL);

	g_assert(priv->refcnt > 0);
	priv->refcnt--;

	if (priv->refcnt == 0) {
		gdome_xml_n_unref (priv->gnode, exc);
		g_free (self);
	}
}
