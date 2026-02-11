glade_eprop_accel_load (GladeEditorProperty *eprop,
			GladeProperty       *property)
{
	GladeEditorPropertyClass *parent_class =
		g_type_class_peek_parent (GLADE_EDITOR_PROPERTY_GET_CLASS (eprop));
	GladeEPropAccel *eprop_accel = GLADE_EPROP_ACCEL (eprop);
	gchar           *accels;


	parent_class->load (eprop, property);

	if (property == NULL) return;

	if ((accels =
	     glade_accels_make_string (g_value_get_boxed (property->value))) != NULL)
	{
		gtk_entry_set_text (GTK_ENTRY (eprop_accel->entry), accels);
		g_free (accels);
	}
	else
		gtk_entry_set_text (GTK_ENTRY (eprop_accel->entry), "");

}
