tracker_sparql_builder_delete_open (TrackerSparqlBuilder* self, const gchar* graph) {
	TrackerSparqlBuilderState _tmp0_ = 0;
	TrackerSparqlBuilderState _tmp1_ = 0;
	TrackerSparqlBuilderState* _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	const gchar* _tmp3_ = NULL;
#line 263 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_return_if_fail (self != NULL);
#line 263 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp0_ = tracker_sparql_builder_get_state (self);
#line 263 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp1_ = _tmp0_;
#line 263 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_return_if_fail (_tmp1_ == TRACKER_SPARQL_BUILDER_STATE_UPDATE);
#line 266 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp2_ = self->priv->states;
#line 266 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp2__length1 = self->priv->states_length1;
#line 266 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_vala_array_add7 (&self->priv->states, &self->priv->states_length1, &self->priv->_states_size_, TRACKER_SPARQL_BUILDER_STATE_DELETE);
#line 267 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp3_ = graph;
#line 267 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	if (_tmp3_ != NULL) {
#line 648 "tracker-builder.c"
		GString* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		gchar* _tmp6_ = NULL;
		gchar* _tmp7_ = NULL;
#line 268 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_tmp4_ = self->priv->str;
#line 268 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_tmp5_ = graph;
#line 268 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_tmp6_ = g_strdup_printf ("DELETE FROM <%s> {\n", _tmp5_);
#line 268 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_tmp7_ = _tmp6_;
#line 268 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		g_string_append (_tmp4_, _tmp7_);
#line 268 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_g_free0 (_tmp7_);
#line 665 "tracker-builder.c"
	} else {
		GString* _tmp8_ = NULL;
#line 270 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_tmp8_ = self->priv->str;
#line 270 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		g_string_append (_tmp8_, "DELETE {\n");
#line 672 "tracker-builder.c"
	}
}
