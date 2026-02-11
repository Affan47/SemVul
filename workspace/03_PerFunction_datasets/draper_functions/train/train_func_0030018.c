tracker_sparql_query_set_location (TrackerSparqlQuery* self, TrackerSourceLocation* location) {
	TrackerSparqlScanner* _tmp0_;
	TrackerSourceLocation _tmp1_;
	GError * _inner_error_ = NULL;
#line 362 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	g_return_if_fail (self != NULL);
#line 362 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	g_return_if_fail (location != NULL);
#line 363 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp0_ = self->priv->scanner;
#line 363 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp1_ = *location;
#line 363 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	tracker_sparql_scanner_seek (_tmp0_, &_tmp1_);
#line 364 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->priv->size = 0;
#line 365 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->priv->index = 0;
#line 3598 "tracker-sparql-query.c"
	{
#line 367 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		tracker_sparql_query_next (self, &_inner_error_);
#line 367 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		if (_inner_error_ != NULL) {
#line 367 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
			if (_inner_error_->domain == TRACKER_SPARQL_ERROR) {
#line 3606 "tracker-sparql-query.c"
				goto __catch2_tracker_sparql_error;
			}
#line 367 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 367 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
			g_clear_error (&_inner_error_);
#line 367 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
			return;
#line 3615 "tracker-sparql-query.c"
		}
	}
	goto __finally2;
	__catch2_tracker_sparql_error:
	{
		GError* e = NULL;
#line 366 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		e = _inner_error_;
#line 366 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		_inner_error_ = NULL;
#line 370 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		g_critical ("internal error: next in set_location failed");
#line 366 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		_g_error_free0 (e);
#line 3630 "tracker-sparql-query.c"
	}
	__finally2:
#line 366 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	if (_inner_error_ != NULL) {
#line 366 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 366 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		g_clear_error (&_inner_error_);
#line 366 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
		return;
#line 3641 "tracker-sparql-query.c"
	}
}
