rate_current_track(guint rating)
{
	if (rating >= 0 && rating <= 5) {
		gchar           buf[64];
		xmmsc_result_t *res;

		snprintf(buf, 63, "Rated track: %d", rating - 1);
		wejpscroller_shortmessage_show(WEJPSCROLLER(scroller), buf, 50);

		res = xmmsc_medialib_entry_property_set_int_with_source(connection,
		                                                        trackinfo_get_id(&track),
		                                                        "client/generic",
		                                                        "rating", rating);
		xmmsc_result_unref(res);
	}
}
