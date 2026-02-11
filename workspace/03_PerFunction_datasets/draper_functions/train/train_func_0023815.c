read_only_map_tests_real_set_up (GeeTestCase* base) {
	ReadOnlyMapTests * self;
	GeeTreeMap* _tmp0_ = NULL;
	GeeMap* _tmp1_ = NULL;
	GeeMap* _tmp2_ = NULL;
	GeeMap* _tmp3_ = NULL;
	self = (ReadOnlyMapTests*) base;
	_tmp0_ = gee_tree_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL, NULL);
	_g_object_unref0 (self->test_map);
	self->test_map = (GeeMap*) _tmp0_;
	_tmp1_ = self->test_map;
	_tmp2_ = gee_map_get_read_only_view (_tmp1_);
	_tmp3_ = _tmp2_;
	_g_object_unref0 (self->ro_map);
	self->ro_map = _tmp3_;
}
