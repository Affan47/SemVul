test_query_properties (void)
{
	gchar *order_by, *sort_order, *group;
	gboolean show_deleted;
	guint start_index, max_results;
	GDataContactsQuery *query = gdata_contacts_query_new_with_limits ("q", 1, 10);


	g_object_set (G_OBJECT (query),
	              "order-by", "lastmodified",
	              "show-deleted", TRUE,
	              "sort-order", "descending",
	              "group", "http://www.google.com/feeds/contacts/groups/jo@gmail.com/base/1234a",
	              NULL);


	g_object_get (G_OBJECT (query),
	              "order-by", &order_by,
	              "show-deleted", &show_deleted,
	              "sort-order", &sort_order,
	              "group", &group,
	              "start-index", &start_index,
	              "max-results", &max_results,
	              NULL);

	g_assert_cmpstr (order_by, ==, "lastmodified");
	g_assert (show_deleted == TRUE);
	g_assert_cmpstr (sort_order, ==, "descending");
	g_assert_cmpstr (group, ==, "http://www.google.com/feeds/contacts/groups/jo@gmail.com/base/1234a");
	g_assert_cmpuint (start_index, ==, 1);
	g_assert_cmpuint (max_results, ==, 10);

	g_free (order_by);
	g_free (sort_order);
	g_free (group);

	g_object_unref (query);
}
