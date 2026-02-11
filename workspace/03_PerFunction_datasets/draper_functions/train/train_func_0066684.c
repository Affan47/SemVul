history_entry_construct (GType object_type, GDateTime* date, const gchar* name, guint duration) {
	HistoryEntry* self = NULL;
	GDateTime* _tmp0_ = NULL;
	GDateTime* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	guint _tmp4_ = 0U;
	g_return_val_if_fail (date != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	self = (HistoryEntry*) g_type_create_instance (object_type);
	_tmp0_ = date;
	_tmp1_ = _g_date_time_ref0 (_tmp0_);
	_g_date_time_unref0 (self->date);
	self->date = _tmp1_;
	_tmp2_ = name;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->name);
	self->name = _tmp3_;
	_tmp4_ = duration;
	self->duration = _tmp4_;
	return self;
}
