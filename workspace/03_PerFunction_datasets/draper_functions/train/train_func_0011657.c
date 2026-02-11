test_query_etag (void)
{
	GDataPicasaWebQuery *query = gdata_picasaweb_query_new (NULL);


	g_test_bug ("613529");

#define CHECK_ETAG(C) \
	gdata_query_set_etag (GDATA_QUERY (query), "foobar");		\
	(C);								\
	g_assert (gdata_query_get_etag (GDATA_QUERY (query)) == NULL);

	CHECK_ETAG (gdata_picasaweb_query_set_visibility (query, GDATA_PICASAWEB_PUBLIC))
	CHECK_ETAG (gdata_picasaweb_query_set_thumbnail_size (query, "500x430"))
	CHECK_ETAG (gdata_picasaweb_query_set_image_size (query, "1024x768"))
	CHECK_ETAG (gdata_picasaweb_query_set_tag (query, "tag"))
	CHECK_ETAG (gdata_picasaweb_query_set_bounding_box (query, 0.0, 1.0, 20.0, 12.5))
	CHECK_ETAG (gdata_picasaweb_query_set_location (query, "Somewhere near here"))

#undef CHECK_ETAG

	g_object_unref (query);
}
