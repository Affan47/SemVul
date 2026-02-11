name_for_subject (const guchar *subject,
                  gsize n_subject)
{
	GNode *asn;
	gchar *name;
	GBytes *bytes;

	g_assert (subject);
	g_assert (n_subject);

	bytes = g_bytes_new (subject, n_subject);
	asn = egg_asn1x_create_and_decode (pkix_asn1_tab, "Name", bytes);
	g_return_val_if_fail (asn != NULL, NULL);
	g_bytes_unref (bytes);

	name = egg_dn_read_part (egg_asn1x_node (asn, "rdnSequence", NULL), "CN");
	egg_asn1x_destroy (asn);

	return name;
}
