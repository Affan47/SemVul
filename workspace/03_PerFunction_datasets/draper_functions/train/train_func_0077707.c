abraca_filter_search_box_finalize (GObject* obj) {
	AbracaFilterSearchBox * self;
	self = ABRACA_FILTER_SEARCH_BOX (obj);
	_g_object_unref0 (self->priv->_pending_queries);
	_g_free0 (self->priv->_unsaved_query);
	_g_free0 (self->priv->_current_query);
	_g_object_unref0 (self->priv->test);
	_g_object_unref0 (self->priv->treeview);
	G_OBJECT_CLASS (abraca_filter_search_box_parent_class)->finalize (obj);
}
