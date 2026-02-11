__set_from_xml_node (MidgardDBObject *object, xmlNode *node)
{
	g_assert (object != NULL);
	g_assert (node != NULL);

	MidgardUser *self = MIDGARD_USER (object);
	xmlNode *lnode = NULL;
	gchar *content;


	lnode = __lookup_node (node, "guid");
	g_free ((gchar*) MIDGARD_DBOBJECT (self)->dbpriv->guid);


	lnode = __lookup_node (node, "login");
	content = (gchar *)xmlNodeGetContent (lnode);
	if (content != NULL) {
		g_free (self->priv->login);
		self->priv->login = g_strdup (content);
		g_free (content);
	}


	lnode = __lookup_node (node, "password");
	content = (gchar *)xmlNodeGetContent (lnode);
	if (content != NULL) {
		g_free (self->priv->password);
		self->priv->password = g_strdup (content);
		g_free (content);
	}


	lnode = __lookup_node (node, "active");
	content = (gchar *)xmlNodeGetContent (lnode);
	if (content != NULL) {
		self->priv->active = (gboolean)atoi (content);
		g_free (content);
	}


	lnode = __lookup_node (node, "authtype");
	content = (gchar *)xmlNodeGetContent (lnode);
	if (content != NULL) {
		g_free (self->priv->auth_type);
		self->priv->auth_type = g_strdup (content);
		g_free (content);
	}


	lnode = __lookup_node (node, "authtypeid");
	content = (gchar *)xmlNodeGetContent (lnode);
	if (content != NULL) {
		self->priv->auth_type_id = atoi (content);
		g_free (content);
	}


	lnode = __lookup_node (node, "usertype");
	content = (gchar *)xmlNodeGetContent (lnode);
	if (content != NULL) {
		self->priv->user_type = atoi (content);
		g_free (content);
	}


	lnode = __lookup_node (node, "person");
	content = (gchar *)xmlNodeGetContent (lnode);
	if (content != NULL) {
		g_free (self->priv->person_guid);
		self->priv->person_guid = g_strdup (content);
		g_free (content);
	}
}
