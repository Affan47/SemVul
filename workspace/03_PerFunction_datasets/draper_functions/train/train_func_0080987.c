init_global_tls_stuff (void)
{
  int ret;


  if (gnutls_certificate_allocate_credentials (&xcred) < 0)
    {
      fprintf (stderr, "Certificate allocation memory error\n");
      exit (1);
    }

  if (x509_cafile != NULL)
    {
      ret = gnutls_certificate_set_x509_trust_file (xcred,
                                                    x509_cafile, x509ctype);
      if (ret < 0)
        {
          fprintf (stderr, "Error setting the x509 trust file\n");
        }
      else
        {
          printf ("Processed %d CA certificate(s).\n", ret);
        }
    }
#ifdef ENABLE_PKI
  if (x509_crlfile != NULL)
    {
      ret = gnutls_certificate_set_x509_crl_file (xcred, x509_crlfile,
                                                  x509ctype);
      if (ret < 0)
        {
          fprintf (stderr, "Error setting the x509 CRL file\n");
        }
      else
        {
          printf ("Processed %d CRL(s).\n", ret);
        }
    }
#endif

  load_keys ();

#ifdef ENABLE_OPENPGP
  if (pgp_keyring != NULL)
    {
      ret =
        gnutls_certificate_set_openpgp_keyring_file (xcred, pgp_keyring,
                                                     GNUTLS_OPENPGP_FMT_BASE64);
      if (ret < 0)
        {
          fprintf (stderr, "Error setting the OpenPGP keyring file\n");
        }
    }
#endif

#ifdef ENABLE_SRP
  if (srp_username && srp_passwd)
    {

      if (gnutls_srp_allocate_client_credentials (&srp_cred) < 0)
        {
          fprintf (stderr, "SRP authentication error\n");
        }

      gnutls_srp_set_client_credentials_function (srp_cred,
                                                  srp_username_callback);
    }
#endif

#ifdef ENABLE_PSK

  if (gnutls_psk_allocate_client_credentials (&psk_cred) < 0)
    {
      fprintf (stderr, "PSK authentication error\n");
    }

  if (psk_username && psk_key.data)
    {
      ret = gnutls_psk_set_client_credentials (psk_cred,
                                               psk_username, &psk_key,
                                               GNUTLS_PSK_KEY_HEX);
      if (ret < 0)
        {
          fprintf (stderr, "Error setting the PSK credentials: %s\n",
                   gnutls_strerror (ret));
        }
    }
  gnutls_psk_set_client_credentials_function (psk_cred, psk_callback);
#endif

#ifdef ENABLE_ANON

  if (gnutls_anon_allocate_client_credentials (&anon_cred) < 0)
    {
      fprintf (stderr, "Anonymous authentication error\n");
    }
#endif

}
