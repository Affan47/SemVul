print_verification_res (gnutls_x509_crt_t crt,
                        gnutls_x509_crt_t issuer,
                        gnutls_x509_crl_t * crl_list, int crl_list_size,
                        unsigned int flags)
{
  unsigned int output;
  int comma = 0;
  int ret;

  ret = gnutls_x509_crt_verify (crt, &issuer, 1, flags, &output);
  if (ret < 0)
    error (EXIT_FAILURE, 0, "verification error: %s", gnutls_strerror (ret));

  if (output & GNUTLS_CERT_INVALID)
    {
      fprintf (outfile, "Not verified");
      comma = 1;
    }
  else
    {
      fprintf (outfile, "Verified");
      comma = 1;
    }

  if (output & GNUTLS_CERT_SIGNER_NOT_CA)
    {
      if (comma)
        fprintf (outfile, ", ");
      fprintf (outfile, "Issuer is not a CA");
      comma = 1;
    }

  if (output & GNUTLS_CERT_INSECURE_ALGORITHM)
    {
      if (comma)
        fprintf (outfile, ", ");
      fprintf (outfile, "Insecure algorithm");
      comma = 1;
    }

  if (output & GNUTLS_CERT_NOT_ACTIVATED)
    {
      if (comma)
        fprintf (outfile, ", ");
      fprintf (outfile, "Not activated");
      comma = 1;
    }

  if (output & GNUTLS_CERT_EXPIRED)
    {
      if (comma)
        fprintf (outfile, ", ");
      fprintf (outfile, "Expired");
      comma = 1;
    }

  ret = gnutls_x509_crt_check_revocation (crt, crl_list, crl_list_size);
  if (ret < 0)
    error (EXIT_FAILURE, 0, "revocation check: %s", gnutls_strerror (ret));

  if (ret == 1)
    {
      if (comma)
        fprintf (outfile, ", ");
      comma = 1;
      fprintf (outfile, "Revoked");
    }
}
