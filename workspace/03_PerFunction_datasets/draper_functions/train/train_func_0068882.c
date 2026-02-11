_vala_main (gchar** args, int args_length1) {
	gint result = 0;
	GDateTime* _tmp0_;
	GDateTime* now;
	GDateTime* _tmp1_;
	gint _tmp2_ = 0;
	Serializer* _tmp3_;
	gchar* _tmp4_ = NULL;
	gchar* buffer;
	gint buffer_length1;
	gint _buffer_size_;
	_tmp0_ = g_date_time_new_now_utc ();
	now = _tmp0_;
	_tmp1_ = now;
	_tmp2_ = g_date_time_get_microsecond (_tmp1_);
	g_random_set_seed ((guint32) _tmp2_);
	setlocale (LC_ALL, "");
	_tmp3_ = serializer_new (DISPLAY_FORMAT_AUTOMATIC, 10, 9);
	_g_object_unref0 (result_serializer);
	result_serializer = _tmp3_;
	_tmp4_ = g_new0 (gchar, 1024);
	buffer = _tmp4_;
	buffer_length1 = 1024;
	_buffer_size_ = buffer_length1;
	while (TRUE) {
		FILE* _tmp5_;
		FILE* _tmp6_;
		gchar* _tmp7_;
		gint _tmp7__length1;
		const gchar* _tmp8_ = NULL;
		gchar* _tmp9_;
		gchar* line;
		const gchar* _tmp10_;
		gchar* _tmp11_ = NULL;
		gboolean _tmp12_ = FALSE;
		gboolean _tmp13_ = FALSE;
		gboolean _tmp14_ = FALSE;
		const gchar* _tmp15_;
		gboolean _tmp17_;
		gboolean _tmp19_;
		gboolean _tmp21_;
		const gchar* _tmp22_;
		_tmp5_ = stdout;
		fprintf (_tmp5_, "> ");
		_tmp6_ = stdin;
		_tmp7_ = buffer;
		_tmp7__length1 = buffer_length1;
		_tmp8_ = fgets (_tmp7_, _tmp7__length1, _tmp6_);
		_tmp9_ = g_strdup (_tmp8_);
		line = _tmp9_;
		_tmp10_ = line;
		_tmp11_ = string_strip (_tmp10_);
		_g_free0 (line);
		line = _tmp11_;
		_tmp15_ = line;
		if (_tmp15_ == NULL) {
			_tmp14_ = TRUE;
		} else {
			const gchar* _tmp16_;
			_tmp16_ = line;
			_tmp14_ = g_strcmp0 (_tmp16_, "exit") == 0;
		}
		_tmp17_ = _tmp14_;
		if (_tmp17_) {
			_tmp13_ = TRUE;
		} else {
			const gchar* _tmp18_;
			_tmp18_ = line;
			_tmp13_ = g_strcmp0 (_tmp18_, "quit") == 0;
		}
		_tmp19_ = _tmp13_;
		if (_tmp19_) {
			_tmp12_ = TRUE;
		} else {
			const gchar* _tmp20_;
			_tmp20_ = line;
			_tmp12_ = g_strcmp0 (_tmp20_, "") == 0;
		}
		_tmp21_ = _tmp12_;
		if (_tmp21_) {
			_g_free0 (line);
			break;
		}
		_tmp22_ = line;
		solve (_tmp22_);
		_g_free0 (line);
	}
	result = EXIT_SUCCESS;
	buffer = (g_free (buffer), NULL);
	_g_date_time_unref0 (now);
	return result;
}
