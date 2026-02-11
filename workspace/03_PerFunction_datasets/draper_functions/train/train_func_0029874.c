string_to_ip (unsigned char *ip, const char *str)
{
  int len = strlen (str);
  int ret;

#if HAVE_IPV6
  if (strchr (str, ':') != NULL || len > 16)
    {
      ret = inet_pton (AF_INET6, str, ip);
      if (ret <= 0)
        {
          fprintf (stderr, "Error in IPv6 address %s\n", str);
          exit (1);
        }


      return 16;
    }
  else
#endif
    {
      ret = inet_pton (AF_INET, str, ip);
      if (ret <= 0)
        {
          fprintf (stderr, "Error in IPv4 address %s\n", str);
          exit (1);
        }

      return 4;
    }

}
