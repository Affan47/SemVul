fso_gsm_plus_cnmi_issue (FsoGsmPlusCNMI* self, gint mode, gint mt, gint bm, gint ds, gint bfr) {
	gchar* result = NULL;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	gchar* _tmp5_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = mode;
	_tmp1_ = mt;
	_tmp2_ = bm;
	_tmp3_ = ds;
	_tmp4_ = bfr;
	_tmp5_ = g_strdup_printf ("+CNMI=%d,%d,%d,%d,%d", _tmp0_, _tmp1_, _tmp2_, _tmp3_, _tmp4_);
	result = _tmp5_;
	return result;
}
