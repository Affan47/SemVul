get_sign_status (int server)
{
  const char *msg;

  if (batch)
    {
      return cfg.signing_key;
    }
  else
    {
      if (server)
        msg =
          "Will the certificate be used for signing (DHE and RSA-EXPORT ciphersuites)? (y/N): ";
      else
        msg =
          "Will the certificate be used for signing (required for TLS)? (y/N): ";
      return read_yesno (msg);
    }
}
