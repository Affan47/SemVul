g_date_time_to_string (GDateTime* self) {
	gchar* result = NULL;
	gchar* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = g_date_time_format (self, "%FT%H:%M:%S%z");
	result = _tmp0_;
	return result;
}
