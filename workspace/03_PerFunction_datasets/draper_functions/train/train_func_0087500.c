test_key_to_public (Test *test, gconstpointer unused)
{
	gcry_sexp_t pubkey = NULL;
	guchar id1[20], id2[20];
	gboolean ret;
	guchar *p;


	ret = gkm_sexp_key_to_public (test->rsakey, &pubkey);
	g_assert (ret);
	g_assert (pubkey != NULL);

	p = gcry_pk_get_keygrip (test->rsakey, id1);
	g_return_if_fail (p == id1);
	p = gcry_pk_get_keygrip (pubkey, id2);
	g_return_if_fail (p == id2);

	g_assert (memcmp (id1, id2, sizeof (id1)) == 0);

	gcry_sexp_release (pubkey);


	ret = gkm_sexp_key_to_public (test->dsakey, &pubkey);
	g_assert (ret);
	g_assert (pubkey != NULL);

	p = gcry_pk_get_keygrip (test->dsakey, id1);
	g_return_if_fail (p == id1);
	p = gcry_pk_get_keygrip (pubkey, id2);
	g_return_if_fail (p == id2);

	g_assert (memcmp (id1, id2, sizeof (id1)) == 0);

	gcry_sexp_release (pubkey);

}
