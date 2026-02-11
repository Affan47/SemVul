tracker_store_queue_turtle_import_data_free (gpointer _data) {
	TrackerStoreQueueTurtleImportData* _data_;
	_data_ = _data;
#line 22 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	_g_object_unref0 (_data_->file);
#line 22 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	_g_free0 (_data_->client_id);
#line 22 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	g_slice_free (TrackerStoreQueueTurtleImportData, _data_);
#line 2991 "tracker-store.c"
}
