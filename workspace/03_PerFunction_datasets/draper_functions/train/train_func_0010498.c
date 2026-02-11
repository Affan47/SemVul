gog_series_class_init (GogSeriesClass *klass)
{
	static GogObjectRole const roles[] = {
		{ N_("Point"), "GogSeriesElement",	0,
		  GOG_POSITION_SPECIAL, GOG_POSITION_SPECIAL, GOG_OBJECT_NAME_BY_ROLE,
		  role_series_element_can_add, NULL,
		  role_series_element_allocate,
		  role_series_element_post_add,
		  role_series_element_pre_remove, NULL },
		{ N_("Regression curve"), "GogRegCurve",	1,
		  GOG_POSITION_SPECIAL, GOG_POSITION_SPECIAL, GOG_OBJECT_NAME_BY_TYPE,
		  regression_curve_can_add,
		  NULL,
		  NULL,
		  regression_curve_post_add,
		  regression_curve_pre_remove,
		  NULL },
		{ N_("Trend line"), "GogTrendLine",	2,
		  GOG_POSITION_SPECIAL, GOG_POSITION_SPECIAL, GOG_OBJECT_NAME_BY_TYPE,
		  regression_curve_can_add,
		  NULL,
		  NULL,
		  regression_curve_post_add,
		  regression_curve_pre_remove,
		  NULL },
		{ N_("Data labels"), "GogSeriesLabels",	3,
		  GOG_POSITION_SPECIAL, GOG_POSITION_SPECIAL, GOG_OBJECT_NAME_BY_ROLE,
		  role_series_labels_can_add,
		  NULL,
		  NULL,
		  role_series_labels_post_add,
		  NULL,
		  NULL }
	};
	unsigned int i;

	GObjectClass *gobject_klass = (GObjectClass *) klass;
	GogObjectClass *gog_klass = (GogObjectClass *) klass;
	GogStyledObjectClass *style_klass = (GogStyledObjectClass *) klass;

	series_parent_klass = g_type_class_peek_parent (klass);
	gobject_klass->finalize		= gog_series_finalize;
	gobject_klass->set_property	= gog_series_set_property;
	gobject_klass->get_property	= gog_series_get_property;
	klass->has_interpolation	= FALSE;

#ifdef GOFFICE_WITH_GTK
	gog_klass->populate_editor	= gog_series_populate_editor;
#endif
	gog_klass->update		= gog_series_update;
	gog_klass->child_added		= gog_series_child_added;
	gog_klass->child_removed	= gog_series_child_added;
	style_klass->init_style 	= gog_series_init_style;

	gog_klass->use_parent_as_proxy  = TRUE;

	gog_object_register_roles (gog_klass, roles, G_N_ELEMENTS (roles));

	g_object_class_install_property (gobject_klass, SERIES_PROP_HAS_LEGEND,
		g_param_spec_boolean ("has-legend",
			_("Has-legend"),
			_("Should the series show up in legends"),
			TRUE,
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
        g_object_class_install_property (gobject_klass, SERIES_PROP_INTERPOLATION,
		 g_param_spec_string ("interpolation",
			_("Interpolation"),
			_("Type of line interpolation"),
			"linear",
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT | GOG_PARAM_FORCE_SAVE));
	g_object_class_install_property (gobject_klass, SERIES_PROP_INTERPOLATION_SKIP_INVALID,
		g_param_spec_boolean ("interpolation-skip-invalid",
			_("Interpolation skip invalid"),
			_("Should the series interpolation ignore the invalid data"),
			FALSE,
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));
	g_object_class_install_property (gobject_klass, SERIES_PROP_FILL_TYPE,
		g_param_spec_string ("fill-type",
			_("Fill type"),
			_("How to fill the area"),
			"invalid",
			GSF_PARAM_STATIC | G_PARAM_READWRITE | GO_PARAM_PERSISTENT));

	klass->valid_fill_type_list = NULL;


	for (i = 0; i < G_N_ELEMENTS (_fill_type_infos); i++)
		g_assert (_fill_type_infos[i].type == i);
}
