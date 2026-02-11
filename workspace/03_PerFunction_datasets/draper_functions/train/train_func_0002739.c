nautilus_search_hit_set_property (GObject *object,
				  guint arg_id,
				  const GValue *value,
				  GParamSpec *pspec)
{
	NautilusSearchHit *hit;

	hit = NAUTILUS_SEARCH_HIT (object);

	switch (arg_id) {
	case PROP_RELEVANCE:
		hit->details->relevance = g_value_get_double (value);
		break;
	case PROP_FTS_RANK:
		nautilus_search_hit_set_fts_rank (hit, g_value_get_double (value));
		break;
	case PROP_URI:
		nautilus_search_hit_set_uri (hit, g_value_get_string (value));
		break;
	case PROP_MODIFICATION_TIME:
		nautilus_search_hit_set_modification_time (hit, g_value_get_boxed (value));
		break;
	case PROP_ACCESS_TIME:
		nautilus_search_hit_set_access_time (hit, g_value_get_boxed (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, arg_id, pspec);
		break;
	}
}
