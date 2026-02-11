string_to_gvalue (const gchar         *value,
                  TrackerPropertyType  type,
                  GValue              *gvalue,
                  GError             **error)
{
	gint object_id;
	gchar *datetime;

	switch (type) {
	case TRACKER_PROPERTY_TYPE_STRING:
		g_value_init (gvalue, G_TYPE_STRING);
		g_value_set_string (gvalue, value);
		break;
	case TRACKER_PROPERTY_TYPE_INTEGER:
		g_value_init (gvalue, G_TYPE_INT64);
		g_value_set_int64 (gvalue, atoll (value));
		break;
	case TRACKER_PROPERTY_TYPE_BOOLEAN:


		g_value_init (gvalue, G_TYPE_INT64);
		g_value_set_int64 (gvalue, strcmp (value, "true") == 0);
		break;
	case TRACKER_PROPERTY_TYPE_DOUBLE:
		g_value_init (gvalue, G_TYPE_DOUBLE);
		g_value_set_double (gvalue, atof (value));
		break;
	case TRACKER_PROPERTY_TYPE_DATE:
		g_value_init (gvalue, G_TYPE_INT64);
		datetime = g_strdup_printf ("%sT00:00:00Z", value);
		g_value_set_int64 (gvalue, tracker_string_to_date (datetime, NULL, error));
		g_free (datetime);
		break;
	case TRACKER_PROPERTY_TYPE_DATETIME:
		g_value_init (gvalue, TRACKER_TYPE_DATE_TIME);
		tracker_date_time_set_from_string (gvalue, value, error);
		break;
	case TRACKER_PROPERTY_TYPE_RESOURCE:
		object_id = ensure_resource_id (value, NULL);
		g_value_init (gvalue, G_TYPE_INT64);
		g_value_set_int64 (gvalue, object_id);
		break;
	default:
		g_warn_if_reached ();
		break;
	}
}
