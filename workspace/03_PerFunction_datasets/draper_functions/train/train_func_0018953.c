gnm_so_filled_set_property (GObject *obj, guint param_id,
			    GValue const *value, GParamSpec *pspec)
{
	GnmSOFilled *sof = GNM_SO_FILLED (obj);
	char const * str;

	switch (param_id) {
	case SOF_PROP_STYLE:  {
		GOStyle *style = go_style_dup (g_value_get_object (value));
		style->interesting_fields = GO_STYLE_OUTLINE | GO_STYLE_FILL;
		g_object_unref (sof->style);
		sof->style = style;
		break;
	}
	case SOF_PROP_IS_OVAL:
		sof->is_oval = g_value_get_boolean (value);
		break;
	case SOF_PROP_TEXT:
		g_free (sof->text);
		str = g_value_get_string (value);
		sof->text = g_strdup (str == NULL ? "" : str);
		break;
	case SOF_PROP_MARKUP:
		if (sof->markup != NULL)
			pango_attr_list_unref (sof->markup);
		sof->markup = g_value_peek_pointer (value);
		if (sof->markup != NULL)
			pango_attr_list_ref (sof->markup);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, param_id, pspec);
		return;
	}
}
