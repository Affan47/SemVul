tag_data_construct (GType object_type, const gchar* _tag_id, GtkTreeIter* _iter, gboolean _update, gboolean _selected, gint _items, TrackerTagsView* _tv) {
	TagData* self = NULL;
	TrackerTagsView* _tmp0_ = NULL;
	TrackerTagsView* _tmp1_ = NULL;
	GCancellable* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	GtkTreeIter* _tmp5_ = NULL;
	gint _tmp7_ = 0;
	gboolean _tmp8_ = FALSE;
	gboolean _tmp9_ = FALSE;
	g_return_val_if_fail (_tv != NULL, NULL);
	self = (TagData*) g_type_create_instance (object_type);
	g_debug ("tracker-tags-view.vala:33: Creating tag data");
	_tmp0_ = _tv;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->tv);
	self->tv = _tmp1_;
	_tmp2_ = g_cancellable_new ();
	_g_object_unref0 (self->cancellable);
	self->cancellable = _tmp2_;
	_tmp3_ = _tag_id;
	_tmp4_ = g_strdup (_tmp3_);
	_g_free0 (self->tag_id);
	self->tag_id = _tmp4_;
	_tmp5_ = _iter;
	if (_tmp5_ != NULL) {
		GtkTreeIter* _tmp6_ = NULL;
		_tmp6_ = _iter;
		self->iter = *_tmp6_;
	}
	_tmp7_ = _items;
	self->items = _tmp7_;
	_tmp8_ = _update;
	self->update = _tmp8_;
	_tmp9_ = _selected;
	self->selected = _tmp9_;
	return self;
}
