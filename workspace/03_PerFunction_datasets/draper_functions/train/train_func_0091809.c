gnm_sheet_slicer_get_property (GObject *obj, guint property_id,
			       GValue *value, GParamSpec *pspec)
{
	GnmSheetSlicer const *gss = (GnmSheetSlicer const *)obj;
	switch (property_id) {
	case PROP_SHEET : g_value_set_object (value, gss->sheet); break;
	case PROP_RANGE : g_value_set_boxed (value, &gss->range); break;
	case PROP_FIRST_HEADER_ROW : g_value_set_uint (value, gss->first_header_row ); break;
	case PROP_FIRST_DATA_COL : g_value_set_uint (value, gss->first_data_col); break;
	case PROP_FIRST_DATA_ROW : g_value_set_uint (value, gss->first_data_row); break;

	case PROP_SHOW_HEADERS_COL : g_value_set_boolean (value, gss->show.headers_col); break;
	case PROP_SHOW_HEADERS_ROW : g_value_set_boolean (value, gss->show.headers_row); break;
	case PROP_SHOW_STRIPES_COL : g_value_set_boolean (value, gss->show.stripes_col); break;
	case PROP_SHOW_STRIPES_ROW : g_value_set_boolean (value, gss->show.stripes_row); break;
	case PROP_SHOW_LAST_COL    : g_value_set_boolean (value, gss->show.last_col); break;
	case PROP_SHOW_LAST_ROW    : g_value_set_boolean (value, gss->show.last_row); break;

	case PROP_LAYOUT : g_value_set_enum (value, gss->layout); break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, property_id, pspec);
	}
}
