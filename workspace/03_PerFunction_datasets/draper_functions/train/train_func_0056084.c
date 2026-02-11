filter_get_mediainfo_field_string (xmmsv_coll_t *coll,
                                   GHashTable *mediainfo, gchar **val)
{
	gboolean retval = FALSE;
	gchar *attr;
	xmmsv_t *cmdval;

	if (xmmsv_coll_attribute_get (coll, "field", &attr)) {
		cmdval = g_hash_table_lookup (mediainfo, attr);
		if (cmdval != NULL) {
			switch (xmmsv_get_type (cmdval)) {
			case XMMSV_TYPE_STRING:
			{
				const gchar *s;
				xmmsv_get_string (cmdval, &s);
				*val = g_strdup (s);
				retval = TRUE;
				break;
			}
			case XMMSV_TYPE_INT32:
			{
				gint i;
				xmmsv_get_int (cmdval, &i);
				*val = g_strdup_printf ("%d", i);
				retval = TRUE;
				break;
			}
			default:
				break;
			}
		}
	}

	return retval;
}
