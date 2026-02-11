mp_error_code_to_string (ErrorCode error_code) {
	gchar* result = NULL;
	ErrorCode _tmp0_ = 0;
	_tmp0_ = error_code;
	switch (_tmp0_) {
		case ERROR_CODE_NONE:
		{
			gchar* _tmp1_ = NULL;
			_tmp1_ = g_strdup ("ErrorCode.NONE");
			result = _tmp1_;
			return result;
		}
		case ERROR_CODE_INVALID:
		{
			gchar* _tmp2_ = NULL;
			_tmp2_ = g_strdup ("ErrorCode.INVALID");
			result = _tmp2_;
			return result;
		}
		case ERROR_CODE_OVERFLOW:
		{
			gchar* _tmp3_ = NULL;
			_tmp3_ = g_strdup ("ErrorCode.OVERFLOW");
			result = _tmp3_;
			return result;
		}
		case ERROR_CODE_UNKNOWN_VARIABLE:
		{
			gchar* _tmp4_ = NULL;
			_tmp4_ = g_strdup ("ErrorCode.UNKNOWN_VARIABLE");
			result = _tmp4_;
			return result;
		}
		case ERROR_CODE_UNKNOWN_FUNCTION:
		{
			gchar* _tmp5_ = NULL;
			_tmp5_ = g_strdup ("ErrorCode.UNKNOWN_FUNCTION");
			result = _tmp5_;
			return result;
		}
		case ERROR_CODE_UNKNOWN_CONVERSION:
		{
			gchar* _tmp6_ = NULL;
			_tmp6_ = g_strdup ("ErrorCode.UNKNOWN_CONVERSION");
			result = _tmp6_;
			return result;
		}
		case ERROR_CODE_MP:
		{
			gchar* _tmp7_ = NULL;
			_tmp7_ = g_strdup ("ErrorCode.MP");
			result = _tmp7_;
			return result;
		}
		default:
		{
			gchar* _tmp8_ = NULL;
			_tmp8_ = g_strdup ("Unknown parser error");
			result = _tmp8_;
			return result;
		}
	}
}
