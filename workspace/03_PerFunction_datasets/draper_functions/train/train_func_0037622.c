fso_gsm_constants_cssiCodeToString (gint code) {
	gchar* result = NULL;
	gint _tmp0_ = 0;
	_tmp0_ = code;
	switch (_tmp0_) {
		case 0:
		{
			gchar* _tmp1_ = NULL;
			_tmp1_ = g_strdup ("unconditional-forwardings-active");
			result = _tmp1_;
			return result;
		}
		case 1:
		{
			gchar* _tmp2_ = NULL;
			_tmp2_ = g_strdup ("conditional-forwardings-active");
			result = _tmp2_;
			return result;
		}
		case 2:
		{
			gchar* _tmp3_ = NULL;
			_tmp3_ = g_strdup ("forwarded");
			result = _tmp3_;
			return result;
		}
		case 3:
		{
			gchar* _tmp4_ = NULL;
			_tmp4_ = g_strdup ("waiting-call-pending");
			result = _tmp4_;
			return result;
		}
		default:
		{
			gint _tmp5_ = 0;
			gchar* _tmp6_ = NULL;
			gchar* _tmp7_ = NULL;
			gchar* _tmp8_ = NULL;
			gchar* _tmp9_ = NULL;
			_tmp5_ = code;
			_tmp6_ = g_strdup_printf ("%i", _tmp5_);
			_tmp7_ = _tmp6_;
			_tmp8_ = g_strconcat ("<unknown:cssi:", _tmp7_, ">", NULL);
			_tmp9_ = _tmp8_;
			_g_free0 (_tmp7_);
			result = _tmp9_;
			return result;
		}
	}
}
