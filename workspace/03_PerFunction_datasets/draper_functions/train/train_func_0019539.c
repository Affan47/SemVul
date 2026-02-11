g_inetaddr_new (const char* name, int port)
{
  struct sockaddr_in* sa_in;
  struct in_addr inaddr;
  g_inet_addr* ia = NULL;

  if(name==NULL)
     return NULL;

  ia = (g_inet_addr *)malloc(sizeof(g_inet_addr));
  if(ia==NULL)
     return NULL;
  memset(ia, 0, sizeof(g_inet_addr));

  ia->name = (char *)strdup(name);
  ia->ref_count = 1;


  if (inet_aton(name, &inaddr) != 0)
    {
      sa_in = (struct sockaddr_in*) &ia->sa;
      sa_in->sin_family = AF_INET;
      sa_in->sin_port = htons(port);
      memcpy(&sa_in->sin_addr, (char*) &inaddr, sizeof(struct in_addr));
    }
  else
    {
      struct sockaddr_in sa;


      if (g_gethostbyname(name, &sa, NULL))
        {
          sa_in = (struct sockaddr_in*) &ia->sa;
          sa_in->sin_family = AF_INET;
          sa_in->sin_port = htons(port);
          memcpy(&sa_in->sin_addr, &sa.sin_addr, 4);
        }
    }

  return ia;
}
