show_available_ciphers ()
{
  int nid;


#ifndef ENABLE_SMALL
  printf ("The following ciphers and cipher modes are available\n"
	  "for use with " PACKAGE_NAME ".  Each cipher shown below may be\n"
	  "used as a parameter to the --cipher option.  The default\n"
	  "key size is shown as well as whether or not it can be\n"
          "changed with the --keysize directive.  Using a CBC mode\n"
	  "is recommended.\n\n");
#endif

  for (nid = 0; nid < 10000; ++nid)
    {
      const EVP_CIPHER *cipher = EVP_get_cipherbynid (nid);
      if (cipher && cipher_ok (OBJ_nid2sn (nid)))
	{
	  const unsigned int mode = EVP_CIPHER_mode (cipher);
	  if (mode == EVP_CIPH_CBC_MODE
#ifdef ALLOW_NON_CBC_CIPHERS
	      || mode == EVP_CIPH_CFB_MODE || mode == EVP_CIPH_OFB_MODE
#endif
	      )
	    printf ("%s %d bit default key (%s)\n",
		    OBJ_nid2sn (nid),
		    EVP_CIPHER_key_length (cipher) * 8,
		    ((EVP_CIPHER_flags (cipher) & EVP_CIPH_VARIABLE_LENGTH) ?
		     "variable" : "fixed"));
	}
    }
  printf ("\n");
}
