test_issuer_dn (Test *test, gconstpointer unused)
{
	gchar *dn = gcr_certificate_get_issuer_dn (test->certificate);
	g_assert (dn);
	g_assert_cmpstr (dn, ==, "L=ValiCert Validation Network, O=ValiCert, Inc., OU=ValiCert Class 3 Policy Validation Authority, CN=http://www.valicert.com/, EMAIL=info@valicert.com");
	g_free (dn);
}
