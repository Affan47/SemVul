recent_documents_kde_finalize (GObject* obj) {
	RecentDocumentsKDE * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_RECENT_DOCUMENTS_KDE, RecentDocumentsKDE);
	_g_free0 (self->priv->_unique_id);
	_g_free0 (self->priv->_name);
	_g_free0 (self->priv->_description);
	_g_object_unref0 (self->priv->_datahub);
	_g_free0 (self->priv->recent_document_path);
	_g_object_unref0 (self->priv->recent_documents_directory);
	_g_object_unref0 (self->priv->monitor);
	self->priv->ignored_actors = (_vala_array_free (self->priv->ignored_actors, self->priv->ignored_actors_length1, (GDestroyNotify) g_free), NULL);
	_g_regex_unref0 (self->priv->recent_regex);
	_g_regex_unref0 (self->priv->url_regex);
	G_OBJECT_CLASS (recent_documents_kde_parent_class)->finalize (obj);
}
