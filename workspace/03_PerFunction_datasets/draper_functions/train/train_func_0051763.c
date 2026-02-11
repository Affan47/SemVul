test_query_properties (void)
{
	GDataQuery *query;
	gboolean notification_received = FALSE;
	gulong handler_id;

	query = gdata_query_new ("default");

#define CHECK_PROPERTY(cmptype, name_hyphens, name_underscores, default_val, new_val, new_val2, val_type, free_val) \
	{ \
		val_type val; \
 \
		handler_id = g_signal_connect (query, "notify::" name_hyphens, (GCallback) notify_cb, &notification_received); \
 \
		g_assert_##cmptype (gdata_query_get_##name_underscores (query), ==, default_val); \
		g_object_get (query, name_hyphens, &val, NULL); \
		g_assert_##cmptype (val, ==, default_val); \
		if (free_val == TRUE) { \
			g_free ((gpointer) ((guintptr) val)); \
		} \
 \
		notification_received = FALSE; \
		gdata_query_set_##name_underscores (query, new_val); \
		g_assert (notification_received == TRUE); \
 \
		g_assert_##cmptype (gdata_query_get_##name_underscores (query), ==, new_val); \
 \
		notification_received = FALSE; \
		g_object_set (query, name_hyphens, new_val2, NULL); \
		g_assert (notification_received == TRUE); \
 \
		g_assert_##cmptype (gdata_query_get_##name_underscores (query), ==, new_val2); \
 \
		g_signal_handler_disconnect (query, handler_id); \
	}
#define CHECK_PROPERTY_STR(name_hyphens, name_underscores, default_val) \
	CHECK_PROPERTY (cmpstr, name_hyphens, name_underscores, default_val, "new", "new2", gchar*, TRUE)
#define CHECK_PROPERTY_INT64(name_hyphens, name_underscores, default_val) \
	CHECK_PROPERTY (cmpint, name_hyphens, name_underscores, default_val, 123, 5134132, gint64, FALSE)
#define CHECK_PROPERTY_UINT(name_hyphens, name_underscores, default_val) \
	CHECK_PROPERTY (cmpuint, name_hyphens, name_underscores, default_val, 535, 123, guint, FALSE)
#define CHECK_PROPERTY_BOOLEAN(name_hyphens, name_underscores, default_val) \
	CHECK_PROPERTY (cmpuint, name_hyphens, name_underscores, default_val, TRUE, FALSE, gboolean, FALSE)

	CHECK_PROPERTY_STR ("q", q, "default");
	CHECK_PROPERTY_STR ("categories", categories, NULL);
	CHECK_PROPERTY_STR ("author", author, NULL);
	CHECK_PROPERTY_INT64 ("updated-min", updated_min, -1);
	CHECK_PROPERTY_INT64 ("updated-max", updated_max, -1);
	CHECK_PROPERTY_INT64 ("published-min", published_min, -1);
	CHECK_PROPERTY_INT64 ("published-max", published_max, -1);
	CHECK_PROPERTY_UINT ("start-index", start_index, 0);
#define gdata_query_get_is_strict gdata_query_is_strict
	CHECK_PROPERTY_BOOLEAN ("is-strict", is_strict, FALSE);
#undef gdata_query_get_is_strict
	CHECK_PROPERTY_UINT ("max-results", max_results, 0);
	CHECK_PROPERTY_STR ("etag", etag, NULL);

#undef CHECK_PROPERTY_BOOLEAN
#undef CHECK_PROPERTY_UINT
#undef CHECK_PROPERTY_INT64
#undef CHECK_PROPERTY_STR
#undef CHECK_PROPERTY

	g_object_unref (query);
}
