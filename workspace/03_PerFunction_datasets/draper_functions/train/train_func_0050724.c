unity_object_unref (void* object) {
	GObject* o_ptr = NULL;
	void* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	GObject* _tmp2_ = NULL;
	gboolean _tmp7_ = FALSE;
	_tmp0_ = object;
	o_ptr = (GObject*) _tmp0_;
	_tmp2_ = o_ptr;
	if (G_TYPE_CHECK_INSTANCE_TYPE (_tmp2_, G_TYPE_OBJECT)) {
		GObject* _tmp3_ = NULL;
		GType _tmp4_ = 0UL;
		const gchar* _tmp5_ = NULL;
		gboolean _tmp6_ = FALSE;
		_tmp3_ = o_ptr;
		_tmp4_ = G_TYPE_FROM_INSTANCE (_tmp3_);
		_tmp5_ = g_type_name (_tmp4_);
		_tmp6_ = g_str_has_prefix (_tmp5_, "Unity");
		_tmp1_ = _tmp6_;
	} else {
		_tmp1_ = FALSE;
	}
	_tmp7_ = _tmp1_;
	if (_tmp7_) {
		GObject* _tmp8_ = NULL;
		_tmp8_ = o_ptr;
		g_object_unref (_tmp8_);
	} else {
		g_critical ("unity-utils.vala:38: Unable to unref object, invalid object type");
	}
}
