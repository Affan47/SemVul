get_query_uri (GDataQuery *self, const gchar *feed_uri, GString *query_uri, gboolean *params_started)
{
	GDataCalendarQueryPrivate *priv = GDATA_CALENDAR_QUERY (self)->priv;

	#define APPEND_SEP g_string_append_c (query_uri, (*params_started == FALSE) ? '?' : '&'); *params_started = TRUE;


	GDATA_QUERY_CLASS (gdata_calendar_query_parent_class)->get_query_uri (self, feed_uri, query_uri, params_started);

	APPEND_SEP
	if (priv->future_events == TRUE)
		g_string_append (query_uri, "futureevents=true");
	else
		g_string_append (query_uri, "futureevents=false");

	if (priv->order_by != NULL) {
		APPEND_SEP
		g_string_append (query_uri, "orderby=");
		g_string_append_uri_escaped (query_uri, priv->order_by, NULL, FALSE);
	}

	if (priv->recurrence_expansion_start != -1) {
		gchar *recurrence_expansion_start;

		APPEND_SEP
		g_string_append (query_uri, "recurrence-expansion-start=");
		recurrence_expansion_start = gdata_parser_int64_to_iso8601 (priv->recurrence_expansion_start);
		g_string_append (query_uri, recurrence_expansion_start);
		g_free (recurrence_expansion_start);
	}

	if (priv->recurrence_expansion_end != -1) {
		gchar *recurrence_expansion_end;

		APPEND_SEP
		g_string_append (query_uri, "recurrence-expansion-end=");
		recurrence_expansion_end = gdata_parser_int64_to_iso8601 (priv->recurrence_expansion_end);
		g_string_append (query_uri, recurrence_expansion_end);
		g_free (recurrence_expansion_end);
	}

	APPEND_SEP
	if (priv->single_events == TRUE)
		g_string_append (query_uri, "singleevents=true");
	else
		g_string_append (query_uri, "singleevents=false");

	if (priv->sort_order != NULL) {
		APPEND_SEP
		g_string_append (query_uri, "sortorder=");
		g_string_append_uri_escaped (query_uri, priv->sort_order, NULL, FALSE);
	}

	if (priv->start_min != -1) {
		gchar *start_min;

		APPEND_SEP
		g_string_append (query_uri, "start-min=");
		start_min = gdata_parser_int64_to_iso8601 (priv->start_min);
		g_string_append (query_uri, start_min);
		g_free (start_min);
	}

	if (priv->start_max != -1) {
		gchar *start_max;

		APPEND_SEP
		g_string_append (query_uri, "start-max=");
		start_max = gdata_parser_int64_to_iso8601 (priv->start_max);
		g_string_append (query_uri, start_max);
		g_free (start_max);
	}

	if (priv->timezone != NULL) {
		APPEND_SEP
		g_string_append (query_uri, "ctz=");
		g_string_append_uri_escaped (query_uri, priv->timezone, NULL, FALSE);
	}

	if (priv->max_attendees > 0) {
		APPEND_SEP
		g_string_append_printf (query_uri, "max-attendees=%u", priv->max_attendees);
	}

	APPEND_SEP
	if (priv->show_deleted == TRUE) {
		g_string_append (query_uri, "showdeleted=true");
	} else {
		g_string_append (query_uri, "showdeleted=false");
	}
}
