fso_framework_bin_reader_uint32_convert (FsoFrameworkBinReader* self, guint32 val) {
	guint32 result = 0U;
	GDataStreamByteOrder _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, 0U);
	_tmp0_ = self->endianess;
	if (_tmp0_ == G_DATA_STREAM_BYTE_ORDER_BIG_ENDIAN) {
		guint32 _tmp1_ = 0U;
		guint32 _tmp2_ = 0U;
		_tmp1_ = val;
		_tmp2_ = GUINT32_FROM_BE (_tmp1_);
		result = _tmp2_;
		return result;
	} else {
		GDataStreamByteOrder _tmp3_ = 0;
		_tmp3_ = self->endianess;
		if (_tmp3_ == G_DATA_STREAM_BYTE_ORDER_LITTLE_ENDIAN) {
			guint32 _tmp4_ = 0U;
			guint32 _tmp5_ = 0U;
			_tmp4_ = val;
			_tmp5_ = GUINT32_FROM_LE (_tmp4_);
			result = _tmp5_;
			return result;
		} else {
			guint32 _tmp6_ = 0U;
			_tmp6_ = val;
			result = _tmp6_;
			return result;
		}
	}
}
