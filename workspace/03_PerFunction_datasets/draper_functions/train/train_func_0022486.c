tracker_store_task_finalize (TrackerStoreTask* obj) {
	TrackerStoreTask * self;
#line 55 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TRACKER_STORE_TYPE_TASK, TrackerStoreTask);
#line 57 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	_g_free0 (self->client_id);
#line 58 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	_g_error_free0 (self->error);
#line 59 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	(self->callback_target_destroy_notify == NULL) ? NULL : (self->callback_target_destroy_notify (self->callback_target), NULL);
#line 59 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	self->callback = NULL;
#line 59 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	self->callback_target = NULL;
#line 59 "/home/martyn/Source/checkout/gnome/tracker/src/tracker-store/tracker-store.vala"
	self->callback_target_destroy_notify = NULL;
#line 4189 "tracker-store.c"
}
