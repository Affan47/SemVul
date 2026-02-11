_variant_get2 (GVariant* value, int* result_length1, int* result_length2) {
	gchar** _tmp12_;
	int _tmp12__length;
	int _tmp12__size;
	int _tmp12__length1;
	GVariantIter _tmp13_;
	GVariant* _tmp14_;
	_tmp12_ = g_new (gchar*, 5);
	_tmp12__length = 0;
	_tmp12__size = 4;
	_tmp12__length1 = 0;
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
	g_variant_iter_init (&_tmp13_, value);
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
	for (; (_tmp14_ = g_variant_iter_next_value (&_tmp13_)) != NULL; _tmp12__length1++) {
#line 4964 "tracker-bus.c"
		int _tmp12__length2;
		GVariantIter _tmp15_;
		GVariant* _tmp16_;
		_tmp12__length2 = 0;
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
		g_variant_iter_init (&_tmp15_, _tmp14_);
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
		for (; (_tmp16_ = g_variant_iter_next_value (&_tmp15_)) != NULL; _tmp12__length2++) {
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
			if (_tmp12__size == _tmp12__length) {
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
				_tmp12__size = 2 * _tmp12__size;
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
				_tmp12_ = g_renew (gchar*, _tmp12_, _tmp12__size + 1);
#line 4979 "tracker-bus.c"
			}
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
			_tmp12_[_tmp12__length++] = g_variant_dup_string (_tmp16_, NULL);
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
			g_variant_unref (_tmp16_);
#line 4985 "tracker-bus.c"
		}
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
		*result_length2 = _tmp12__length2;
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
		g_variant_unref (_tmp14_);
#line 4991 "tracker-bus.c"
	}
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
	*result_length1 = _tmp12__length1;
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
	_tmp12_[_tmp12__length] = NULL;
#line 294 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-bus/tracker-bus.vala"
	return _tmp12_;
#line 4999 "tracker-bus.c"
}
