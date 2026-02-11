config_nameserver(struct server_state **servers, int *nservers,
                             char *str)
{
  struct ares_addr host;
  struct server_state *newserv;
  char *p, *txtaddr;


  for (p = str; p;)
    {

      while (*p && (ISSPACE(*p) || (*p == ',')))
        p++;
      if (!*p)

        break;


      txtaddr = p;


      while (*p && !ISSPACE(*p) && (*p != ','))
        p++;
      if (*p)

        *p++ = '\0';
      else

        p = NULL;


      if (ares_inet_pton(AF_INET, txtaddr, &host.addrV4) == 1)
        host.family = AF_INET;
      else if (ares_inet_pton(AF_INET6, txtaddr, &host.addrV6) == 1)
        host.family = AF_INET6;
      else
        continue;


      newserv = realloc(*servers, (*nservers + 1) *
                        sizeof(struct server_state));
      if (!newserv)
        return ARES_ENOMEM;


      newserv[*nservers].addr.family = host.family;
      if (host.family == AF_INET)
        memcpy(&newserv[*nservers].addr.addrV4, &host.addrV4,
               sizeof(host.addrV4));
      else
        memcpy(&newserv[*nservers].addr.addrV6, &host.addrV6,
               sizeof(host.addrV6));


      *servers = newserv;
      *nservers += 1;
    }

  return ARES_SUCCESS;
}
