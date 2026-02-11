fso_framework_bin_builder_insert_uint16 (FsoFrameworkBinBuilder* self, guint16 val, gint position) {
	GList* l = NULL;
	gint _tmp0_ = 0;
	GList* _tmp1_ = NULL;
	guint16 _tmp2_ = 0U;
	guint16 _tmp3_ = 0U;
	guint16 _tmp4_ = 0U;
	guint8 _tmp5_ = 0U;
	guint16 _tmp6_ = 0U;
	guint8 _tmp7_ = 0U;
	g_return_if_fail (self != NULL);
	_tmp0_ = position;
	_tmp1_ = fso_framework_bin_builder_get_at (self, _tmp0_, (guint) 1);
	l = _tmp1_;
	_tmp2_ = val;
	_tmp3_ = fso_framework_bin_builder_uint16_convert (self, _tmp2_);
	val = _tmp3_;
	_tmp4_ = val;
	_tmp5_ = fso_framework_bin_builder_nth_byte ((guint64) _tmp4_, (guint) 0);
	l = g_list_insert (l, (gpointer) ((guintptr) _tmp5_), 0);
	_tmp6_ = val;
	_tmp7_ = fso_framework_bin_builder_nth_byte ((guint64) _tmp6_, (guint) 1);
	l = g_list_insert (l, (gpointer) ((guintptr) _tmp7_), 1);
}
