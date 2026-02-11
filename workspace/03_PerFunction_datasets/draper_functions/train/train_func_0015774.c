_dbus_mpris_playlists_set_Orderings (MprisPlaylists* self, GVariant* _value) {
	gchar** value = NULL;
	int value_length1;
	gchar** _tmp64_;
	int _tmp64__length;
	int _tmp64__size;
	int _tmp64__length1;
	GVariantIter _tmp65_;
	GVariant* _tmp66_;
	_tmp64_ = g_new (gchar*, 5);
	_tmp64__length = 0;
	_tmp64__size = 4;
	_tmp64__length1 = 0;
	g_variant_iter_init (&_tmp65_, _value);
	for (; (_tmp66_ = g_variant_iter_next_value (&_tmp65_)) != NULL; _tmp64__length1++) {
		if (_tmp64__size == _tmp64__length) {
			_tmp64__size = 2 * _tmp64__size;
			_tmp64_ = g_renew (gchar*, _tmp64_, _tmp64__size + 1);
		}
		_tmp64_[_tmp64__length++] = g_variant_dup_string (_tmp66_, NULL);
		g_variant_unref (_tmp66_);
	}
	value_length1 = _tmp64__length1;
	_tmp64_[_tmp64__length] = NULL;
	value = _tmp64_;
	mpris_playlists_set_Orderings (self, value, value_length1);
	value = (_vala_array_free (value, value_length1, (GDestroyNotify) g_free), NULL);
}
