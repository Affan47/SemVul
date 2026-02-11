go_pixbuf_finalize (GObject *obj)
{
	GOPixbuf *pixbuf = GO_PIXBUF (obj);
	if (pixbuf->pixbuf)
		g_object_unref (pixbuf->pixbuf);
	if (pixbuf->surface)
		cairo_surface_destroy (pixbuf->surface);
	(parent_klass->finalize) (obj);
}
