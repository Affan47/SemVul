char_box_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	CharBox * self;
	GtkDrawingArea* _tmp0_ = NULL;
	parent_class = G_OBJECT_CLASS (char_box_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = CHAR_BOX (obj);
	_tmp0_ = (GtkDrawingArea*) gtk_drawing_area_new ();
	_g_object_unref0 (self->priv->area);
	self->priv->area = g_object_ref_sink (_tmp0_);
	g_signal_connect_object ((GtkWidget*) self->priv->area, "draw", (GCallback) _char_box_draw_request_gtk_widget_draw, self, 0);
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) self->priv->area);
	return obj;
}
