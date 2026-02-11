_gnutls_cipher_priority (gnutls_session_t session,
                         gnutls_cipher_algorithm_t algorithm)
{
  unsigned int i;
  for (i = 0; i < session->internals.priorities.cipher.algorithms; i++)
    {
      if (session->internals.priorities.cipher.priority[i] == algorithm)
        return i;
    }
  return -1;
}
