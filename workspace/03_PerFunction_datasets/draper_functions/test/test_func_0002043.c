statement_bind_gvalue (TrackerDBStatement *stmt,
                       gint               *idx,
                       const GValue       *value)
{
	GType type;

	type = G_VALUE_TYPE (value);
	switch (type) {
	case G_TYPE_STRING:
		tracker_db_statement_bind_text (stmt, (*idx)++, g_value_get_string (value));
		break;
	case G_TYPE_INT64:
		tracker_db_statement_bind_int (stmt, (*idx)++, g_value_get_int64 (value));
		break;
	case G_TYPE_DOUBLE:
		tracker_db_statement_bind_double (stmt, (*idx)++, g_value_get_double (value));
		break;
	default:
		if (type == TRACKER_TYPE_DATE_TIME) {
			tracker_db_statement_bind_double (stmt, (*idx)++, tracker_date_time_get_time (value));
			tracker_db_statement_bind_int (stmt, (*idx)++, tracker_date_time_get_local_date (value));
			tracker_db_statement_bind_int (stmt, (*idx)++, tracker_date_time_get_local_time (value));
		} else {
			g_warning ("Unknown type for binding: %s\n", G_VALUE_TYPE_NAME (value));
		}
		break;
	}
}
