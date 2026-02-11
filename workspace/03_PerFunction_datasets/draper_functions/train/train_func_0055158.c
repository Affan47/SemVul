common_init_class (GogXYZPlotClass *klass, gboolean is_3d)
{
	GogPlotClass *gog_plot_klass = (GogPlotClass*) klass;
	GObjectClass *gobject_klass = (GObjectClass *) klass;
	GogObjectClass *gog_object_klass = (GogObjectClass *) klass;

	gobject_klass->set_property = gog_xyz_surface_plot_set_property;
	gobject_klass->get_property = gog_xyz_surface_plot_get_property;
	gobject_klass->finalize = gog_xyz_surface_finalize;
	g_object_class_install_property (gobject_klass, XYZ_SURFACE_PROP_ROWS,
		g_param_spec_uint ("rows",
			_("Rows"),
			_("Number of rows"),
			2, 1000, 10,
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
	g_object_class_install_property (gobject_klass, XYZ_SURFACE_PROP_AUTO_ROWS,
		g_param_spec_boolean ("auto-rows",
			_("Auto Rows"),
			_("Whether the rows limits should be evaluated"),
			TRUE,
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
	g_object_class_install_property (gobject_klass, XYZ_SURFACE_PROP_COLUMNS,
		g_param_spec_uint ("columns",
			_("Columns"),
			_("Number of columns"),
			2, 1000, 10,
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
	g_object_class_install_property (gobject_klass, XYZ_SURFACE_PROP_AUTO_COLUMNS,
		g_param_spec_boolean ("auto-columns",
			_("Auto Columns"),
			_("Whether the columns limits should be evaluated"),
			TRUE,
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
	if (is_3d) {
		g_object_class_install_property (gobject_klass, XYZ_SURFACE_PROP_EXTRA1,
			g_param_spec_string ("missing-as",
				_("Missing as"),
				_("How to deal with missing data"),
				"invalid",
				GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
		{
			static GogSeriesDimDesc dimensions[] = {
				{ N_("X"), GOG_SERIES_REQUIRED, FALSE,
				  GOG_DIM_VALUE, GOG_MS_DIM_VALUES },
				{ N_("Y"), GOG_SERIES_REQUIRED, FALSE,
				  GOG_DIM_VALUE, GOG_MS_DIM_VALUES },
				{ N_("Z"), GOG_SERIES_REQUIRED, FALSE,
				  GOG_DIM_VALUE, GOG_MS_DIM_VALUES },
			};
			gog_plot_klass->desc.series.dim = dimensions;
			gog_plot_klass->desc.series.num_dim = G_N_ELEMENTS (dimensions);
		}
	} else {
		g_object_class_install_property (gobject_klass, XYZ_SURFACE_PROP_EXTRA1,
			g_param_spec_boolean ("as-density",
				_("As density"),
				_("Display the data as density instead or raw data"),
				TRUE,
				GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
		{
			static GogSeriesDimDesc dimensions[] = {
				{ N_("X"), GOG_SERIES_REQUIRED, FALSE,
				  GOG_DIM_VALUE, GOG_MS_DIM_VALUES },
				{ N_("Y"), GOG_SERIES_REQUIRED, FALSE,
				  GOG_DIM_VALUE, GOG_MS_DIM_VALUES },
			};
			gog_plot_klass->desc.series.dim = dimensions;
			gog_plot_klass->desc.series.num_dim = G_N_ELEMENTS (dimensions);
		}
	}

	gog_object_klass->update	= gog_xyz_surface_plot_update;

#ifdef GOFFICE_WITH_GTK
	gog_object_klass->populate_editor	= gog_xyz_surface_plot_populate_editor;
#endif

}
