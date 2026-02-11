convert_keysym_state_to_string(guint keysym, GdkModifierType mask, guint keycode)
{
	gchar *name;

	name = gtk_accelerator_name(keysym, mask);
	if (keysym == 0)
	{
		gchar *tmp;

		tmp = name;
		name = g_strdup_printf("%s0x%02x", tmp, keycode);
		g_free(tmp);
	}

	return name;
}
