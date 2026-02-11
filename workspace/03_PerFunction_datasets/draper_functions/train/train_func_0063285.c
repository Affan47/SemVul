tracker_sparql_builder_graph_open (TrackerSparqlBuilder* self, const gchar* graph) {
	TrackerSparqlBuilderState _tmp0_ = 0;
	TrackerSparqlBuilderState _tmp1_ = 0;
	TrackerSparqlBuilderState _tmp2_ = 0;
	TrackerSparqlBuilderState _tmp3_ = 0;
	TrackerSparqlBuilderState _tmp4_ = 0;
	TrackerSparqlBuilderState _tmp5_ = 0;
	TrackerSparqlBuilderState _tmp6_ = 0;
	TrackerSparqlBuilderState _tmp7_ = 0;
	TrackerSparqlBuilderState _tmp8_ = 0;
	TrackerSparqlBuilderState _tmp9_ = 0;
	TrackerSparqlBuilderState* _tmp10_ = NULL;
	gint _tmp10__length1 = 0;
	GString* _tmp11_ = NULL;
	const gchar* _tmp12_ = NULL;
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_return_if_fail (self != NULL);
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_return_if_fail (graph != NULL);
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp0_ = tracker_sparql_builder_get_state (self);
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp1_ = _tmp0_;
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp2_ = tracker_sparql_builder_get_state (self);
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp3_ = _tmp2_;
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp4_ = tracker_sparql_builder_get_state (self);
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp5_ = _tmp4_;
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp6_ = tracker_sparql_builder_get_state (self);
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp7_ = _tmp6_;
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp8_ = tracker_sparql_builder_get_state (self);
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp9_ = _tmp8_;
#line 302 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_return_if_fail (((((_tmp1_ == TRACKER_SPARQL_BUILDER_STATE_INSERT) || (_tmp3_ == TRACKER_SPARQL_BUILDER_STATE_DELETE)) || (_tmp5_ == TRACKER_SPARQL_BUILDER_STATE_OBJECT)) || (_tmp7_ == TRACKER_SPARQL_BUILDER_STATE_WHERE)) || (_tmp9_ == TRACKER_SPARQL_BUILDER_STATE_GRAPH));
#line 305 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp10_ = self->priv->states;
#line 305 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp10__length1 = self->priv->states_length1;
#line 305 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_vala_array_add8 (&self->priv->states, &self->priv->states_length1, &self->priv->_states_size_, TRACKER_SPARQL_BUILDER_STATE_GRAPH);
#line 306 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp11_ = self->priv->str;
#line 306 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp12_ = graph;
#line 306 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_string_append_printf (_tmp11_, "GRAPH <%s> {\n", _tmp12_);
#line 814 "tracker-builder.c"
}
