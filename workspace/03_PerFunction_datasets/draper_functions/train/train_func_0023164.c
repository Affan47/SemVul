style_shape_free(gpointer data, gpointer userdata)
{
	START_FUNC
	struct shape *shape=(struct shape *)data;
	if (shape) {
		if (shape->name) g_free(shape->name);
		if (shape->source) g_free(shape->source);
		if (shape->svg) g_object_unref(G_OBJECT(shape->svg));
		if (shape->mask) cairo_surface_destroy(shape->mask);
		g_free(shape);
	}
	END_FUNC
}
