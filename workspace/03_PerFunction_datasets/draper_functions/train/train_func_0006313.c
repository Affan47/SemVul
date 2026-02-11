tracker_sparql_connection_get (GCancellable* cancellable, GError** error) {
	TrackerSparqlConnection* result = NULL;
	GCancellable* _tmp0_;
	TrackerSparqlConnection* _tmp1_ = NULL;
	TrackerSparqlConnection* _tmp2_;
	GError * _inner_error_ = NULL;
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp0_ = cancellable;
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp1_ = tracker_sparql_backend_get_internal (_tmp0_, &_inner_error_);
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	_tmp2_ = _tmp1_;
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	if (_inner_error_ != NULL) {
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
		if ((((_inner_error_->domain == TRACKER_SPARQL_ERROR) || (_inner_error_->domain == G_IO_ERROR)) || (_inner_error_->domain == G_DBUS_ERROR)) || (_inner_error_->domain == G_SPAWN_ERROR)) {
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_propagate_error (error, _inner_error_);
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			return NULL;
#line 4080 "tracker-backend.c"
		} else {
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			g_clear_error (&_inner_error_);
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
			return NULL;
#line 4088 "tracker-backend.c"
		}
	}
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	result = _tmp2_;
#line 382 "/home/martyn/Source/tracker/src/libtracker-sparql-backend/tracker-backend.vala"
	return result;
#line 4095 "tracker-backend.c"
}
