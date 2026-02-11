tracker_status_wait_context_finalize (GObject* obj) {
	TrackerStatusWaitContext * self;
#line 29 "/home/martyn/Source/tracker/src/tracker-store/tracker-status.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TRACKER_STATUS_TYPE_WAIT_CONTEXT, TrackerStatusWaitContext);
#line 30 "/home/martyn/Source/tracker/src/tracker-store/tracker-status.vala"
	(self->callback_target_destroy_notify == NULL) ? NULL : (self->callback_target_destroy_notify (self->callback_target), NULL);
#line 30 "/home/martyn/Source/tracker/src/tracker-store/tracker-status.vala"
	self->callback = NULL;
#line 30 "/home/martyn/Source/tracker/src/tracker-store/tracker-status.vala"
	self->callback_target = NULL;
#line 30 "/home/martyn/Source/tracker/src/tracker-store/tracker-status.vala"
	self->callback_target_destroy_notify = NULL;
#line 29 "/home/martyn/Source/tracker/src/tracker-store/tracker-status.vala"
	G_OBJECT_CLASS (tracker_status_wait_context_parent_class)->finalize (obj);
#line 665 "tracker-status.c"
}
