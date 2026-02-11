check_pubkey_sign (int n, gcry_sexp_t skey, gcry_sexp_t pkey, int algo)
{
  gcry_error_t rc;
  gcry_sexp_t sig, badhash, hash;
  int dataidx;
  static const char baddata[] =
    "(data\n (flags pkcs1)\n"
    " (hash sha1 #11223344556677889900AABBCCDDEEFF10203041#))\n";
  static struct
  {
    const char *data;
    int algo;
    int expected_rc;
  } datas[] =
    {
      { "(data\n (flags pkcs1)\n"
	" (hash sha1 #11223344556677889900AABBCCDDEEFF10203040#))\n",
	GCRY_PK_RSA,
	0 },
      { "(data\n (flags oaep)\n"
	" (hash sha1 #11223344556677889900AABBCCDDEEFF10203040#))\n",
	0,
	GPG_ERR_CONFLICT },


      { "(data\n (flags pkcs1)\n"
	" (hash oid.1.3.14.3.2.29 "
        "       #11223344556677889900AABBCCDDEEFF10203040#))\n",
	GCRY_PK_RSA,
	0 },
      {	"(data\n (flags )\n"
	" (hash sha1 #11223344556677889900AABBCCDDEEFF10203040#))\n",
	0,
	GPG_ERR_CONFLICT },
      {	"(data\n (flags pkcs1)\n"
	" (hash foo #11223344556677889900AABBCCDDEEFF10203040#))\n",
	GCRY_PK_RSA,
	GPG_ERR_DIGEST_ALGO },
      {	"(data\n (flags )\n" " (value #11223344556677889900AA#))\n",
	0,
	0 },
      {	"(data\n (flags )\n" " (value #0090223344556677889900AA#))\n",
	0,
	0 },
      { "(data\n (flags raw)\n" " (value #11223344556677889900AA#))\n",
	0,
	0 },
      {	"(data\n (flags pkcs1)\n"
	" (value #11223344556677889900AA#))\n",
	GCRY_PK_RSA,
	GPG_ERR_CONFLICT },
      { "(data\n (flags raw foo)\n"
	" (value #11223344556677889900AA#))\n",
	0,
	GPG_ERR_INV_FLAG },
      { "(data\n (flags pss)\n"
	" (hash sha1 #11223344556677889900AABBCCDDEEFF10203040#))\n",
	GCRY_PK_RSA,
	0 },
      { "(data\n (flags pss)\n"
	" (hash sha1 #11223344556677889900AABBCCDDEEFF10203040#)\n"
        " (random-override #4253647587980912233445566778899019283747#))\n",
	GCRY_PK_RSA,
	0 },
      { NULL }
    };

  (void)n;

  rc = gcry_sexp_sscan (&badhash, NULL, baddata, strlen (baddata));
  if (rc)
    die ("converting data failed: %s\n", gpg_strerror (rc));

  for (dataidx = 0; datas[dataidx].data; dataidx++)
    {
      if (datas[dataidx].algo && datas[dataidx].algo != algo)
	continue;

      if (verbose)
	fprintf (stderr, "  signature test %d\n", dataidx);

      rc = gcry_sexp_sscan (&hash, NULL, datas[dataidx].data,
			    strlen (datas[dataidx].data));
      if (rc)
	die ("converting data failed: %s\n", gpg_strerror (rc));

      rc = gcry_pk_sign (&sig, hash, skey);
      if (gcry_err_code (rc) != datas[dataidx].expected_rc)
	fail ("gcry_pk_sign failed: %s\n", gpg_strerror (rc));

      if (!rc)
	verify_one_signature (pkey, hash, badhash, sig);

      gcry_sexp_release (sig);
      sig = NULL;
      gcry_sexp_release (hash);
      hash = NULL;
    }

  gcry_sexp_release (badhash);
}
