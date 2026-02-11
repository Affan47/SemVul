tracker_sparql_query_last (TrackerSparqlQuery* self) {
	TrackerSparqlTokenType result = 0;
	gint _tmp0_;
	gint last_index;
	TrackerSparqlQueryTokenInfo* _tmp1_;
	gint _tmp1__length1;
	TrackerSparqlQueryTokenInfo _tmp2_;
	TrackerSparqlTokenType _tmp3_;
#line 329 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	g_return_val_if_fail (self != NULL, 0);
#line 330 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp0_ = self->priv->index;
#line 330 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	last_index = ((_tmp0_ + TRACKER_SPARQL_QUERY_BUFFER_SIZE) - 1) % TRACKER_SPARQL_QUERY_BUFFER_SIZE;
#line 331 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp1_ = self->priv->tokens;
#line 331 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp1__length1 = self->priv->tokens_length1;
#line 331 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp2_ = _tmp1_[last_index];
#line 331 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp3_ = _tmp2_.type;
#line 331 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	result = _tmp3_;
#line 331 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	return result;
#line 3286 "tracker-sparql-query.c"
}
