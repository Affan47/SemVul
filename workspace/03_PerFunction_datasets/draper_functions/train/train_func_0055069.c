BIO_new_socket (int sock, int close_flag)
{
  BIO *bio;

  bio = (BIO *) malloc (sizeof (BIO));
  if (!bio)
    return NULL;

  bio->fd = GNUTLS_INT_TO_POINTER (sock);

  return bio;
}
