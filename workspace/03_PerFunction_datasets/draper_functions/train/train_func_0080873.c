e_source_ldap_set_filter (ESourceLDAP *extension,
                          const gchar *filter)
{
	gboolean needs_parens;
	gchar *new_filter;

	g_return_if_fail (E_IS_SOURCE_LDAP (extension));

	needs_parens =
		(filter != NULL) && (*filter != '\0') &&
		!g_str_has_prefix (filter, "(") &&
		!g_str_has_suffix (filter, ")");

	g_mutex_lock (&extension->priv->property_lock);

	if (needs_parens)
		new_filter = g_strdup_printf ("(%s)", filter);
	else
		new_filter = g_strdup (filter);

	if (g_strcmp0 (extension->priv->filter, new_filter) == 0) {
		g_mutex_unlock (&extension->priv->property_lock);
		g_free (new_filter);
		return;
	}

	g_free (extension->priv->filter);
	extension->priv->filter = new_filter;

	g_mutex_unlock (&extension->priv->property_lock);

	g_object_notify (G_OBJECT (extension), "filter");
}
