tracker_resources_disable_signals (TrackerResources* self) {
	guint _tmp0_ = 0U;
#line 346 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
	g_return_if_fail (self != NULL);
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
	tracker_data_remove_insert_statement_callback (_tracker_resources_on_statement_inserted_tracker_statement_callback, self);
#line 348 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
	tracker_data_remove_delete_statement_callback (_tracker_resources_on_statement_deleted_tracker_statement_callback, self);
#line 349 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
	tracker_data_remove_commit_statement_callback (_tracker_resources_on_statements_committed_tracker_commit_callback, self);
#line 350 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
	tracker_data_remove_rollback_statement_callback (_tracker_resources_on_statements_rolled_back_tracker_commit_callback, self);
#line 352 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
	_tmp0_ = self->priv->signal_timeout;
#line 352 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
	if (_tmp0_ != ((guint) 0)) {
#line 2899 "tracker-resources.c"
		guint _tmp1_ = 0U;
#line 353 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
		_tmp1_ = self->priv->signal_timeout;
#line 353 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-resources.vala"
		g_source_remove (_tmp1_);
#line 2905 "tracker-resources.c"
	}
}
