tracker_sparql_query_finalize (GObject* obj) {
	TrackerSparqlQuery * self;
#line 191 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TRACKER_SPARQL_TYPE_QUERY, TrackerSparqlQuery);
#line 192 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_object_unref0 (self->priv->scanner);
#line 195 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->priv->tokens = (g_free (self->priv->tokens), NULL);
#line 211 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_free0 (self->priv->query_string);
#line 214 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_object_unref0 (self->expression);
#line 215 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_object_unref0 (self->pattern);
#line 217 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_free0 (self->priv->current_graph);
#line 218 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_free0 (self->priv->current_subject);
#line 220 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_free0 (self->priv->current_predicate);
#line 226 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_hash_table_unref0 (self->priv->prefix_map);
#line 229 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	__g_list_free__g_object_unref0_0 (self->bindings);
#line 231 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tracker_sparql_context_unref0 (self->context);
#line 238 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	self->priv->base_uuid = (g_free (self->priv->base_uuid), NULL);
#line 239 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_hash_table_unref0 (self->priv->blank_nodes);
#line 191 "/home/martyn/Source/tracker/src/libtracker-data/tracker-sparql-query.vala"
	G_OBJECT_CLASS (tracker_sparql_query_parent_class)->finalize (obj);
#line 10317 "tracker-sparql-query.c"
}
