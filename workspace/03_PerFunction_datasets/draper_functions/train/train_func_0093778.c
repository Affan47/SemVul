calculate_markup (GcrCertificate *self)
{
	gchar *label = NULL;
	gchar *issuer;
	gchar *markup;

	g_object_get (self, "label", &label, NULL);
	issuer = gcr_certificate_get_issuer_name (self);

	if (issuer)
		markup = g_markup_printf_escaped ("%s\n<small>Issued by: %s</small>", label, issuer);
	else
		markup = g_markup_printf_escaped ("%s\n<small>Issued by: <i>No name</i></small>", label);

	g_free (label);
	g_free (issuer);
	return markup;
}
