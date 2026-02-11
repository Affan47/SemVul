tracker_store_wal_hook (gint n_pages) {
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	GError * _inner_error_ = NULL;
#line 267 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	_tmp0_ = n_pages;
#line 267 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	g_debug ("WAL: %d pages", _tmp0_);
#line 269 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	_tmp1_ = n_pages;
#line 269 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	if (_tmp1_ >= 10000) {
#line 272 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
		tracker_store_wal_checkpoint ();
#line 1760 "tracker-store.c"
	} else {
		gint _tmp2_ = 0;
#line 273 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
		_tmp2_ = n_pages;
#line 273 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
		if (_tmp2_ >= 1000) {
#line 1767 "tracker-store.c"
			gboolean _tmp3_ = FALSE;
#line 274 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
			_tmp3_ = g_atomic_int_compare_and_exchange ((volatile gint *) (&tracker_store_checkpointing), 0, 1);
#line 274 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
			if (_tmp3_) {
#line 1773 "tracker-store.c"
				{
					GThreadPool* _tmp4_ = NULL;
#line 277 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					_tmp4_ = tracker_store_checkpoint_pool;
#line 277 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					g_thread_pool_push (_tmp4_, (gpointer) ((gintptr) TRUE), &_inner_error_);
#line 277 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					if (_inner_error_ != NULL) {
#line 1782 "tracker-store.c"
						goto __catch24_g_error;
					}
				}
				goto __finally24;
				__catch24_g_error:
				{
					GError* e = NULL;
					GError* _tmp5_ = NULL;
					const gchar* _tmp6_ = NULL;
#line 276 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					e = _inner_error_;
#line 276 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					_inner_error_ = NULL;
#line 279 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					_tmp5_ = e;
#line 279 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					_tmp6_ = _tmp5_->message;
#line 279 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					g_warning ("%s", _tmp6_);
#line 280 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					g_atomic_int_set ((volatile gint *) (&tracker_store_checkpointing), 0);
#line 276 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					_g_error_free0 (e);
#line 1806 "tracker-store.c"
				}
				__finally24:
#line 276 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
				if (_inner_error_ != NULL) {
#line 276 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 276 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					g_clear_error (&_inner_error_);
#line 276 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
					return;
#line 1817 "tracker-store.c"
				}
			}
		}
	}
}
