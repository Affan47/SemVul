test_categories (gconstpointer service)
{
	GDataAPPCategories *app_categories;
	GList *categories;
	GError *error = NULL;
	gchar *category_label, *old_locale;

	gdata_test_mock_server_start_trace (mock_server, "categories");

	app_categories = gdata_youtube_service_get_categories (GDATA_YOUTUBE_SERVICE (service), NULL, &error);
	g_assert_no_error (error);
	g_assert (GDATA_IS_APP_CATEGORIES (app_categories));
	g_clear_error (&error);

	categories = gdata_app_categories_get_categories (app_categories);
	g_assert_cmpint (g_list_length (categories), >, 0);
	g_assert (GDATA_IS_YOUTUBE_CATEGORY (categories->data));


	category_label = g_strdup (gdata_category_get_label (GDATA_CATEGORY (categories->data)));

	g_object_unref (app_categories);


	old_locale = g_strdup (gdata_service_get_locale (GDATA_SERVICE (service)));
	gdata_service_set_locale (GDATA_SERVICE (service), "it");

	app_categories = gdata_youtube_service_get_categories (GDATA_YOUTUBE_SERVICE (service), NULL, &error);
	g_assert_no_error (error);
	g_assert (GDATA_IS_APP_CATEGORIES (app_categories));
	g_clear_error (&error);

	categories = gdata_app_categories_get_categories (app_categories);
	g_assert_cmpint (g_list_length (categories), >, 0);
	g_assert (GDATA_IS_YOUTUBE_CATEGORY (categories->data));


	g_assert_cmpstr (category_label, !=, gdata_category_get_label (GDATA_CATEGORY (categories->data)));

	g_object_unref (app_categories);
	g_free (category_label);


	gdata_service_set_locale (GDATA_SERVICE (service), old_locale);
	g_free (old_locale);

	gdata_mock_server_end_trace (mock_server);
}
