do_check_one_pubkey (int n, gcry_sexp_t skey, gcry_sexp_t pkey,
		     const unsigned char *grip, int algo, int flags)
{
 if (flags & FLAG_SIGN)
   check_pubkey_sign (n, skey, pkey, algo);
 if (flags & FLAG_CRYPT)
   check_pubkey_crypt (n, skey, pkey, algo);
 if (grip && (flags & FLAG_GRIP))
   check_pubkey_grip (n, grip, skey, pkey, algo);
}
