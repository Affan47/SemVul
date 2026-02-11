tracker_sparql_pattern_construct (GType object_type, TrackerSparqlQuery* query) {
	TrackerSparqlPattern * self = NULL;
	TrackerSparqlQuery* _tmp0_;
	TrackerSparqlQuery* _tmp1_;
	TrackerSparqlExpression* _tmp2_;
#line 177 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	g_return_val_if_fail (query != NULL, NULL);
#line 177 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	self = (TrackerSparqlPattern*) g_object_new (object_type, NULL);
#line 178 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	_tmp0_ = query;
#line 178 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	self->priv->query = _tmp0_;
#line 179 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	_tmp1_ = query;
#line 179 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	_tmp2_ = _tmp1_->expression;
#line 179 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	self->priv->expression = _tmp2_;
#line 177 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-pattern.vala"
	return self;
#line 1612 "tracker-sparql-pattern.c"
}
