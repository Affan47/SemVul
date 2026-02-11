ganv_canvas_set_property(GObject*      object,
                         guint         prop_id,
                         const GValue* value,
                         GParamSpec*   pspec)
{
	g_return_if_fail(object != NULL);
	g_return_if_fail(GANV_IS_CANVAS(object));

	GanvCanvas* canvas = GANV_CANVAS(object);

	switch (prop_id) {
	case PROP_WIDTH:
		ganv_canvas_resize(canvas, g_value_get_double(value), canvas->height);
		break;
	case PROP_HEIGHT:
		ganv_canvas_resize(canvas, canvas->width, g_value_get_double(value));
		break;
	case PROP_DIRECTION:
		ganv_canvas_set_direction(canvas, (GanvDirection)g_value_get_enum(value));
		break;
	case PROP_FONT_SIZE:
		ganv_canvas_set_font_size(canvas, g_value_get_double(value));
		break;
	case PROP_LOCKED:
		canvas->locked = g_value_get_boolean(value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}
