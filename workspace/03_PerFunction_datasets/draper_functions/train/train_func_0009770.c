tracker_sparql_query_get_internal_error (TrackerSparqlQuery* self, const gchar* msg) {
	GError* result = NULL;
	TrackerSparqlQueryTokenInfo* _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	gint _tmp1_ = 0;
	TrackerSparqlQueryTokenInfo _tmp2_ = {0};
	TrackerSourceLocation _tmp3_ = {0};
	gint _tmp4_ = 0;
	TrackerSparqlQueryTokenInfo* _tmp5_ = NULL;
	gint _tmp5__length1 = 0;
	gint _tmp6_ = 0;
	TrackerSparqlQueryTokenInfo _tmp7_ = {0};
	TrackerSourceLocation _tmp8_ = {0};
	gint _tmp9_ = 0;
	const gchar* _tmp10_ = NULL;
	gchar* _tmp11_ = NULL;
	gchar* _tmp12_ = NULL;
	GError* _tmp13_ = NULL;
	GError* _tmp14_ = NULL;
#line 346 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	g_return_val_if_fail (self != NULL, NULL);
#line 346 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	g_return_val_if_fail (msg != NULL, NULL);
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp0_ = self->priv->tokens;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp0__length1 = self->priv->tokens_length1;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp1_ = self->priv->index;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp2_ = _tmp0_[_tmp1_];
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp3_ = _tmp2_.begin;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp4_ = _tmp3_.line;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp5_ = self->priv->tokens;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp5__length1 = self->priv->tokens_length1;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp6_ = self->priv->index;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp7_ = _tmp5_[_tmp6_];
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp8_ = _tmp7_.begin;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp9_ = _tmp8_.column;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp10_ = msg;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp11_ = g_strdup_printf ("%d.%d: %s", _tmp4_, _tmp9_, _tmp10_);
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp12_ = _tmp11_;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp13_ = g_error_new_literal (TRACKER_SPARQL_ERROR, TRACKER_SPARQL_ERROR_INTERNAL, _tmp12_);
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_tmp14_ = _tmp13_;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	_g_free0 (_tmp12_);
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	result = _tmp14_;
#line 347 "/home/martyn/Source/checkout/gnome/tracker/src/libtracker-data/tracker-sparql-query.vala"
	return result;
#line 3468 "tracker-sparql-query.c"
}
