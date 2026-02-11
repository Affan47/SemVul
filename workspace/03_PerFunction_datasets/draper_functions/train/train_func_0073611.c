gst_tool_set_property (GObject      *object,
		       guint         prop_id,
		       const GValue *value,
		       GParamSpec   *pspec)
{
	GstTool *tool = GST_TOOL (object);

	switch (prop_id) {
	case PROP_NAME:
		tool->name = g_value_dup_string (value);
		break;
	case PROP_TITLE:
		tool->title = g_value_dup_string (value);
		break;
	case PROP_ICON:
		tool->icon = g_value_dup_string (value);
		break;
	case PROP_SHOW_LOCK_BUTTON:
		tool->show_lock_button = g_value_get_boolean (value);
		break;
	}
}
