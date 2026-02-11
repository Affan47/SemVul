dvb_player_thread_find_element (void* av, void* bv) {
	gint result = 0;
	GstElement* a = NULL;
	void* _tmp0_ = NULL;
	GstElement* _tmp1_ = NULL;
	GstElement* b = NULL;
	void* _tmp2_ = NULL;
	GstElement* _tmp3_ = NULL;
	GstElement* _tmp4_ = NULL;
	GstElement* _tmp5_ = NULL;
	_tmp0_ = av;
	_tmp1_ = _gst_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, GST_TYPE_ELEMENT, GstElement));
	a = _tmp1_;
	_tmp2_ = bv;
	_tmp3_ = _gst_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp2_, GST_TYPE_ELEMENT, GstElement));
	b = _tmp3_;
	_tmp4_ = a;
	_tmp5_ = b;
	if (_tmp4_ == _tmp5_) {
		result = 0;
		_gst_object_unref0 (b);
		_gst_object_unref0 (a);
		return result;
	} else {
		result = 1;
		_gst_object_unref0 (b);
		_gst_object_unref0 (a);
		return result;
	}
	_gst_object_unref0 (b);
	_gst_object_unref0 (a);
}
