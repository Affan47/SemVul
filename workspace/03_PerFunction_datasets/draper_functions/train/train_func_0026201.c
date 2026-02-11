tracker_tags_view_construct (GType object_type, GList* _files) {
	TrackerTagsView * self = NULL;
	GList* _tmp4_;
	GCancellable* _tmp5_;
	GtkListStore* _tmp6_;
	GError * _inner_error_ = NULL;
	self = (TrackerTagsView*) g_object_new (object_type, NULL);
	{
		TrackerSparqlConnection* _tmp0_ = NULL;
		TrackerSparqlConnection* _tmp1_;
		_tmp0_ = tracker_sparql_connection_get (NULL, &_inner_error_);
		_tmp1_ = _tmp0_;
		if (_inner_error_ != NULL) {
			goto __catch13_g_error;
		}
		_g_object_unref0 (self->priv->connection);
		self->priv->connection = _tmp1_;
	}
	goto __finally13;
	__catch13_g_error:
	{
		GError* e = NULL;
		GError* _tmp2_;
		const gchar* _tmp3_;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp2_ = e;
		_tmp3_ = _tmp2_->message;
		g_warning ("tracker-tags-view.vala:94: Could not get Sparql connection: %s", _tmp3_);
		_g_error_free0 (e);
	}
	__finally13:
	if (_inner_error_ != NULL) {
		__g_list_free__g_free0_0 (_files);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp4_ = _files;
	_files = NULL;
	__g_list_free__g_free0_0 (self->priv->files);
	self->priv->files = _tmp4_;
	_tmp5_ = g_cancellable_new ();
	_g_object_unref0 (self->priv->cancellable);
	self->priv->cancellable = _tmp5_;
	_tmp6_ = gtk_list_store_new ((gint) TRACKER_TAGS_VIEW_COL_N_COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
	_g_object_unref0 (self->priv->store);
	self->priv->store = _tmp6_;
	tracker_tags_view_create_ui (self);
	__g_list_free__g_free0_0 (_files);
	return self;
}
