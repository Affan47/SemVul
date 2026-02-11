rb_cell_renderer_rating_class_init (RBCellRendererRatingClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (class);
	GtkCellRendererClass *cell_class = GTK_CELL_RENDERER_CLASS (class);

	object_class->get_property = rb_cell_renderer_rating_get_property;
	object_class->set_property = rb_cell_renderer_rating_set_property;

	cell_class->get_size = rb_cell_renderer_rating_get_size;
	cell_class->render   = rb_cell_renderer_rating_render;
	cell_class->activate = rb_cell_renderer_rating_activate;

	class->priv = g_new0 (RBCellRendererRatingClassPrivate, 1);


	rb_rating_install_rating_property (object_class, PROP_RATING);


	rb_cell_renderer_rating_signals[RATED] =
		g_signal_new ("rated",
			      G_OBJECT_CLASS_TYPE (object_class),
			      G_SIGNAL_RUN_LAST,
			      G_STRUCT_OFFSET (RBCellRendererRatingClass, rated),
			      NULL, NULL,
			      rb_marshal_VOID__STRING_DOUBLE,
			      G_TYPE_NONE,
			      2,
			      G_TYPE_STRING,
			      G_TYPE_DOUBLE);

	g_type_class_add_private (class, sizeof (RBCellRendererRatingPrivate));
}
