gog_chart_get_property (GObject *obj, guint param_id,
			GValue *value, GParamSpec *pspec)
{
	GogChart *chart = GOG_CHART (obj);
	GString *string;
	char buffer[G_ASCII_DTOSTR_BUF_SIZE];

	switch (param_id) {
	case CHART_PROP_CARDINALITY_VALID:
		g_value_set_boolean (value, chart->cardinality_valid);
		break;
	case CHART_PROP_PLOT_AREA:
		string = g_string_new ("");
		g_string_append (string, g_ascii_dtostr (buffer, sizeof (buffer), chart->plot_area.x));
		g_string_append_c (string, ' ');
		g_string_append (string, g_ascii_dtostr (buffer, sizeof (buffer), chart->plot_area.y));
		g_string_append_c (string, ' ');
		g_string_append (string, g_ascii_dtostr (buffer, sizeof (buffer), chart->plot_area.w));
		g_string_append_c (string, ' ');
		g_string_append (string, g_ascii_dtostr (buffer, sizeof (buffer), chart->plot_area.h));
		g_value_set_string (value, string->str);
		g_string_free (string, TRUE);
		break;
	case CHART_PROP_PLOT_AREA_IS_MANUAL:
		g_value_set_boolean (value, chart->is_plot_area_manual);
		break;
	case CHART_PROP_X_POS:
		g_value_set_int (value, chart->x_pos);
		break;
	case CHART_PROP_Y_POS:
		g_value_set_int (value, chart->y_pos);
		break;
	case CHART_PROP_COLUMNS:
		g_value_set_int (value, chart->cols);
		break;
	case CHART_PROP_ROWS:
		g_value_set_int (value, chart->rows);
		break;

	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 break;
	}
}
