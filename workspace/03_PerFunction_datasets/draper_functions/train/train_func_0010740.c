tracker_sparql_builder_delete_close (TrackerSparqlBuilder* self) {
	TrackerSparqlBuilderState _tmp0_ = 0;
	TrackerSparqlBuilderState _tmp1_ = 0;
	TrackerSparqlBuilderState _tmp2_ = 0;
	TrackerSparqlBuilderState _tmp3_ = 0;
	TrackerSparqlBuilderState _tmp4_ = 0;
	TrackerSparqlBuilderState _tmp5_ = 0;
	gint _tmp8_ = 0;
	GString* _tmp9_ = NULL;
#line 281 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_return_if_fail (self != NULL);
#line 281 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp0_ = tracker_sparql_builder_get_state (self);
#line 281 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp1_ = _tmp0_;
#line 281 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp2_ = tracker_sparql_builder_get_state (self);
#line 281 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp3_ = _tmp2_;
#line 281 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_return_if_fail ((_tmp1_ == TRACKER_SPARQL_BUILDER_STATE_DELETE) || (_tmp3_ == TRACKER_SPARQL_BUILDER_STATE_OBJECT));
#line 284 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp4_ = tracker_sparql_builder_get_state (self);
#line 284 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp5_ = _tmp4_;
#line 284 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	if (_tmp5_ == TRACKER_SPARQL_BUILDER_STATE_OBJECT) {
#line 712 "tracker-builder.c"
		GString* _tmp6_ = NULL;
		gint _tmp7_ = 0;
#line 285 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_tmp6_ = self->priv->str;
#line 285 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		g_string_append (_tmp6_, " .\n");
#line 286 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		self->priv->states_length1 = self->priv->states_length1 - 3;
#line 286 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
		_tmp7_ = self->priv->states_length1;
#line 723 "tracker-builder.c"
	}
#line 288 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp8_ = self->priv->states_length1;
#line 288 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	self->priv->states_length1 = _tmp8_ - 1;
#line 290 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	_tmp9_ = self->priv->str;
#line 290 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-sparql/tracker-builder.vala"
	g_string_append (_tmp9_, "}\n");
#line 733 "tracker-builder.c"
}
