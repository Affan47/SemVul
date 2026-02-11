tracker_sparql_builder_finalize (GObject* obj) {
	TrackerSparqlBuilder * self;
#line 57 "/home/martyn/Source/tracker/src/libtracker-sparql/tracker-builder.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TRACKER_SPARQL_TYPE_BUILDER, TrackerSparqlBuilder);
#line 160 "/home/martyn/Source/tracker/src/libtracker-sparql/tracker-builder.vala"
	self->priv->states = (g_free (self->priv->states), NULL);
#line 161 "/home/martyn/Source/tracker/src/libtracker-sparql/tracker-builder.vala"
	_g_string_free0 (self->priv->str);
#line 57 "/home/martyn/Source/tracker/src/libtracker-sparql/tracker-builder.vala"
	G_OBJECT_CLASS (tracker_sparql_builder_parent_class)->finalize (obj);
#line 2577 "tracker-builder.c"
}
