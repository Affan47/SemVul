__lambda7_ (Block2Data* _data2_, GeeSet* added, GeeSet* removed, const gchar* m, FolksPersona* a, FolksGroupDetailsChangeReason r) {
	AggregationTests * self;
	GeeSet* _tmp0_ = NULL;
	GeeSet* _tmp1_ = NULL;
#line 274 "/home/treitter/collabora/folks/tests/folks/aggregation.vala"
	self = _data2_->self;
#line 274 "/home/treitter/collabora/folks/tests/folks/aggregation.vala"
	g_return_if_fail (added != NULL);
#line 274 "/home/treitter/collabora/folks/tests/folks/aggregation.vala"
	g_return_if_fail (removed != NULL);
#line 276 "/home/treitter/collabora/folks/tests/folks/aggregation.vala"
	_tmp0_ = added;
#line 276 "/home/treitter/collabora/folks/tests/folks/aggregation.vala"
	_tmp1_ = removed;
#line 276 "/home/treitter/collabora/folks/tests/folks/aggregation.vala"
	_aggregation_tests_test_linkable_properties_individuals_changed (self, FALSE, (guint) 5, (GeeCollection*) _tmp0_, _tmp1_, &_data2_->individual1, &_data2_->individual2);
#line 1428 "aggregation.c"
}
