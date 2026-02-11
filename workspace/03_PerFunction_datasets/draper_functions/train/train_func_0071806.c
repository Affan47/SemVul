glade_property_class_is_object (GladePropertyClass  *klass,
				GladeProjectFormat   fmt)
{
	g_return_val_if_fail (GLADE_IS_PROPERTY_CLASS (klass), FALSE);

 	return (GLADE_IS_PARAM_SPEC_OBJECTS (klass->pspec) ||
		(G_IS_PARAM_SPEC_OBJECT(klass->pspec) &&
		 klass->pspec->value_type != GDK_TYPE_PIXBUF &&
		 !(fmt == GLADE_PROJECT_FORMAT_LIBGLADE &&
		   klass->pspec->value_type == GTK_TYPE_ADJUSTMENT)));
}
