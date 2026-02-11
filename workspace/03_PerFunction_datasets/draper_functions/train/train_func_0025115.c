cd_color_swatch_dup (const CdColorSwatch *src)
{
	CdColorSwatch *dest;
	g_return_val_if_fail (src != NULL, NULL);
	dest = cd_color_swatch_new ();
	dest->name = g_strdup (src->name);
	cd_color_lab_copy (&src->value, &dest->value);
	return dest;
}
