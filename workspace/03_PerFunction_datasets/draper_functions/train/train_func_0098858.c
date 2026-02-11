gog_chart_set_property (GObject *obj, guint param_id,
			 GValue const *value, GParamSpec *pspec)
{
	GogChart *chart = GOG_CHART (obj);
	char **str_doubles;
	char const *str;
	gboolean changed = FALSE;

	switch (param_id) {
	case CHART_PROP_PLOT_AREA:
		str = g_value_get_string (value);
		str_doubles = g_strsplit (str, " ", 4);
		if (g_strv_length (str_doubles) != 4) {
			g_strfreev (str_doubles);
			break;
		}
		chart->plot_area.x = g_ascii_strtod (str_doubles[0], NULL);
		chart->plot_area.y = g_ascii_strtod (str_doubles[1], NULL);
		chart->plot_area.w = g_ascii_strtod (str_doubles[2], NULL);
		chart->plot_area.h = g_ascii_strtod (str_doubles[3], NULL);
		g_strfreev (str_doubles);
		break;
	case CHART_PROP_PLOT_AREA_IS_MANUAL:
		chart->is_plot_area_manual = g_value_get_boolean (value);
		break;
	case CHART_PROP_X_POS:
		chart->x_pos = g_value_get_int (value);
		changed = TRUE;
		break;
	case CHART_PROP_Y_POS:
		chart->y_pos = g_value_get_int (value);
		changed = TRUE;
		break;
	case CHART_PROP_COLUMNS:
		chart->cols = g_value_get_int (value);
		changed = TRUE;
		break;
	case CHART_PROP_ROWS:
		chart->rows = g_value_get_int (value);
		changed = TRUE;
		break;
	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 return;
	}

	if (changed) {
		gog_graph_validate_chart_layout (GOG_GRAPH (GOG_OBJECT (chart)->parent));
		gog_object_emit_changed (GOG_OBJECT (obj), TRUE);
	}
}
