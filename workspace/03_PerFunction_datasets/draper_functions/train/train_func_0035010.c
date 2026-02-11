_ip_string_into_sockaddr_in (const gchar *ip_as_string,
    struct sockaddr_in *sockaddr_in, GError **error)
{
  struct addrinfo hints;
  struct addrinfo *result = NULL;
  int retval;

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_flags = AI_NUMERICHOST;
  retval = getaddrinfo (ip_as_string, NULL, &hints, &result);
  if (retval != 0) {
    g_set_error (error, FS_ERROR, FS_ERROR_NETWORK,
        "Invalid IP address %s passed: %s", ip_as_string,
        gai_strerror (retval));
    return FALSE;
  }
  memcpy (sockaddr_in, result->ai_addr, sizeof (struct sockaddr_in));
  freeaddrinfo (result);

  return TRUE;
}
