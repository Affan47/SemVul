tracker_sparql_context_construct_subquery (GType object_type, TrackerSparqlQuery* query, TrackerSparqlContext* parent_context) {
	TrackerSparqlContext* self = NULL;
	TrackerSparqlQuery* _tmp0_;
	TrackerSparqlContext* _tmp1_;
	TrackerSparqlContext* _tmp2_;
	GDestroyNotify _tmp3_;
	GHashTable* _tmp4_;
	GDestroyNotify _tmp5_;
	GHashTable* _tmp6_;
	TrackerSparqlContext* _tmp7_;
	GHashTable* _tmp8_;
	GHashTable* _tmp9_;
	GDestroyNotify _tmp10_;
	GDestroyNotify _tmp11_;
	GHashTable* _tmp12_;
#line 134 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	g_return_val_if_fail (query != NULL, NULL);
#line 134 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	g_return_val_if_fail (parent_context != NULL, NULL);
#line 134 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self = (TrackerSparqlContext*) g_type_create_instance (object_type);
#line 135 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp0_ = query;
#line 135 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->query = _tmp0_;
#line 136 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp1_ = parent_context;
#line 136 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp2_ = _tracker_sparql_context_ref0 (_tmp1_);
#line 136 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tracker_sparql_context_unref0 (self->parent_context);
#line 136 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->parent_context = _tmp2_;
#line 137 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp3_ = g_object_unref;
#line 137 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp4_ = g_hash_table_new_full (_tracker_sparql_variable_hash_ghash_func, _tracker_sparql_variable_equal_gequal_func, _tmp3_, NULL);
#line 137 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_hash_table_unref0 (self->var_set);
#line 137 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->var_set = _tmp4_;
#line 139 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp5_ = g_object_unref;
#line 139 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp6_ = g_hash_table_new_full (_tracker_sparql_variable_hash_ghash_func, _tracker_sparql_variable_equal_gequal_func, _tmp5_, NULL);
#line 139 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_hash_table_unref0 (self->select_var_set);
#line 139 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->select_var_set = _tmp6_;
#line 140 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp7_ = parent_context;
#line 140 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp8_ = _tmp7_->var_map;
#line 140 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp9_ = _g_hash_table_ref0 (_tmp8_);
#line 140 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_hash_table_unref0 (self->var_map);
#line 140 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->var_map = _tmp9_;
#line 141 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp10_ = g_object_unref;
#line 141 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp11_ = g_object_unref;
#line 141 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp12_ = g_hash_table_new_full (_tracker_sparql_variable_hash_ghash_func, _tracker_sparql_variable_equal_gequal_func, _tmp10_, _tmp11_);
#line 141 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_hash_table_unref0 (self->predicate_variable_map);
#line 141 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->predicate_variable_map = _tmp12_;
#line 142 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->scalar_subquery = TRUE;
#line 134 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	return self;
#line 1753 "tracker-sparql-query.c"
}
