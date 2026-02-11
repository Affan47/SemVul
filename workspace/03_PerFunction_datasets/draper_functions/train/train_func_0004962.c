tracker_sparql_expression_translate_expression_as_order_condition (TrackerSparqlExpression* self, GString* sql, GError** error) {
	GString* _tmp0_;
	gssize _tmp1_;
	glong begin;
	GString* _tmp2_;
	TrackerPropertyType _tmp3_ = 0;
	TrackerPropertyType _tmp4_;
	GError * _inner_error_ = NULL;
#line 235 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	g_return_if_fail (self != NULL);
#line 235 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	g_return_if_fail (sql != NULL);
#line 236 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	_tmp0_ = sql;
#line 236 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	_tmp1_ = _tmp0_->len;
#line 236 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	begin = (glong) _tmp1_;
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	_tmp2_ = sql;
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	_tmp3_ = tracker_sparql_expression_translate_expression (self, _tmp2_, &_inner_error_);
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	_tmp4_ = _tmp3_;
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	if (_inner_error_ != NULL) {
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
		if (_inner_error_->domain == TRACKER_SPARQL_ERROR) {
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
			g_propagate_error (error, _inner_error_);
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
			return;
#line 2332 "tracker-sparql-expression.c"
		} else {
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
			g_clear_error (&_inner_error_);
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
			return;
#line 2340 "tracker-sparql-expression.c"
		}
	}
#line 237 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
	if (_tmp4_ == TRACKER_PROPERTY_TYPE_RESOURCE) {
#line 2345 "tracker-sparql-expression.c"
		GString* _tmp5_;
		GString* _tmp6_;
#line 239 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
		_tmp5_ = sql;
#line 239 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
		g_string_insert (_tmp5_, (gssize) begin, "(SELECT Uri FROM Resource WHERE ID = ");
#line 240 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
		_tmp6_ = sql;
#line 240 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-expression.vala"
		g_string_append (_tmp6_, ")");
#line 2356 "tracker-sparql-expression.c"
	}
}
