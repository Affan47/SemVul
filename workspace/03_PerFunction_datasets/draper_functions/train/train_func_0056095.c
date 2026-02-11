_gdata_parsable_get_xml (GDataParsable *self, GString *xml_string, gboolean declare_namespaces)
{
	GDataParsableClass *klass;
	guint length;
	GHashTable *namespaces = NULL;

	g_return_if_fail (GDATA_IS_PARSABLE (self));
	g_return_if_fail (xml_string != NULL);

	klass = GDATA_PARSABLE_GET_CLASS (self);
	g_assert (klass->element_name != NULL);


	if (declare_namespaces == TRUE && klass->get_namespaces != NULL) {
		namespaces = g_hash_table_new (g_str_hash, g_str_equal);
		klass->get_namespaces (self, namespaces);


		g_hash_table_foreach_remove (self->priv->extra_namespaces, (GHRFunc) filter_namespaces_cb, namespaces);
	}


	if (klass->element_namespace != NULL)
		g_string_append_printf (xml_string, "<%s:%s", klass->element_namespace, klass->element_name);
	else
		g_string_append_printf (xml_string, "<%s", klass->element_name);


	if (declare_namespaces == TRUE) {
		g_string_append (xml_string, " xmlns='http://www.w3.org/2005/Atom'");
		if (namespaces != NULL) {
			g_hash_table_foreach (namespaces, (GHFunc) build_namespaces_cb, xml_string);
			g_hash_table_destroy (namespaces);
		}
	}

	g_hash_table_foreach (self->priv->extra_namespaces, (GHFunc) build_namespaces_cb, xml_string);


	if (klass->pre_get_xml != NULL)
		klass->pre_get_xml (self, xml_string);
	g_string_append_c (xml_string, '>');


	length = xml_string->len;


	if (klass->get_xml != NULL)
		klass->get_xml (self, xml_string);


	if (self->priv->extra_xml != NULL && self->priv->extra_xml->str != NULL)
		g_string_append (xml_string, self->priv->extra_xml->str);


	if (xml_string->len == length)
		g_string_overwrite (xml_string, length - 1, "/>");
	else if (klass->element_namespace != NULL)
		g_string_append_printf (xml_string, "</%s:%s>", klass->element_namespace, klass->element_name);
	else
		g_string_append_printf (xml_string, "</%s>", klass->element_name);
}
