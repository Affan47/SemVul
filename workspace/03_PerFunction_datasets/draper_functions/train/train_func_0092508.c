gog_xyz_surface_plot_get_property (GObject *obj, guint param_id,
				   GValue *value, GParamSpec *pspec)
{
	GogXYZPlot *plot = GOG_XYZ_PLOT (obj);

	switch (param_id) {
	case XYZ_SURFACE_PROP_ROWS :
		g_value_set_uint (value, plot->rows);
		break;
	case XYZ_SURFACE_PROP_COLUMNS :
		g_value_set_uint (value, plot->columns);
		break;
	case XYZ_SURFACE_PROP_AUTO_ROWS :
		g_value_set_boolean (value, plot->auto_y);
		break;
	case XYZ_SURFACE_PROP_AUTO_COLUMNS :
		g_value_set_boolean (value, plot->auto_x);
		break;
	case XYZ_SURFACE_PROP_EXTRA1 :
		if (GOG_PLOT (plot)->desc.series.num_dim == 2) {
			if (GOG_IS_CONTOUR_PLOT (plot))
				g_value_set_boolean (value, GOG_XY_CONTOUR_PLOT (plot)->as_density);
			else if (GOG_IS_MATRIX_PLOT (plot))
				g_value_set_boolean (value, GOG_XY_MATRIX_PLOT (plot)->as_density);
			else
				g_value_set_boolean (value, GOG_XY_SURFACE_PLOT (plot)->as_density);
		} else {
			if (GOG_IS_CONTOUR_PLOT (plot))
				g_value_set_string (value, missing_as_string (GOG_XYZ_CONTOUR_PLOT (plot)->missing_as));
			else if (GOG_IS_MATRIX_PLOT (plot))
				g_value_set_string (value, missing_as_string (GOG_XYZ_MATRIX_PLOT (plot)->missing_as));
			else
				g_value_set_string (value, missing_as_string (GOG_XYZ_SURFACE_PLOT (plot)->missing_as));
		}
		break;

	default: G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		 break;
	}
}
