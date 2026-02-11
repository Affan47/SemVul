nautilus_search_hit_get_property (GObject *object,
				  guint arg_id,
				  GValue *value,
				  GParamSpec *pspec)
{
	NautilusSearchHit *hit;

	hit = NAUTILUS_SEARCH_HIT (object);

	switch (arg_id) {
	case PROP_RELEVANCE:
		g_value_set_double (value, hit->details->relevance);
		break;
	case PROP_FTS_RANK:
		g_value_set_double (value, hit->details->fts_rank);
		break;
	case PROP_URI:
		g_value_set_string (value, hit->details->uri);
		break;
	case PROP_MODIFICATION_TIME:
		g_value_set_boxed (value, hit->details->modification_time);
		break;
	case PROP_ACCESS_TIME:
		g_value_set_boxed (value, hit->details->access_time);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, arg_id, pspec);
		break;
	}
}
