get_pka_info (const char *address, unsigned char *fpr)
{
  union
    {
      signed char p[PACKETSZ];
      HEADER h;
    } answer;
  int anslen;
  int qdcount, ancount;
  int rc;
  unsigned char *p, *pend;
  const char *domain;
  char *name;


  domain = strrchr (address, '@');
  if (!domain || domain == address || !domain[1])
    return NULL;

  name = malloc (strlen (address) + 5 + 1);
  memcpy (name, address, domain - address);
  strcpy (stpcpy (name + (domain-address), "._pka."), domain+1);

  anslen = res_query (name, C_IN, T_TXT, answer.p, PACKETSZ);
  xfree (name);
  if (anslen < sizeof(HEADER))
    return NULL;
  if ( (rc=answer.h.rcode) != NOERROR )
    return NULL;


  if (anslen > PACKETSZ)
    return NULL;

  qdcount = ntohs (answer.h.qdcount);
  ancount = ntohs (answer.h.ancount);

  if (!ancount)
    return NULL;

  p = answer.p + sizeof (HEADER);
  pend = answer.p + anslen;

  while (qdcount-- && p < pend)
    {
      rc = dn_skipname (p, pend);
      if (rc == -1)
        return NULL;
      p += rc + QFIXEDSZ;
    }

  if (ancount > 1)
    return NULL;

  while (ancount-- && p <= pend)
    {
      unsigned int type, class, txtlen, n;
      char *buffer, *bufp;

      rc = dn_skipname (p, pend);
      if (rc == -1)
        return NULL;
      p += rc;
      if (p >= pend - 10)
        return NULL;

      type = *p++ << 8;
      type |= *p++;
      class = *p++ << 8;
      class |= *p++;
      p += 4;
      txtlen = *p++ << 8;
      txtlen |= *p++;
      if (type != T_TXT || class != C_IN)
        return NULL;

      buffer = bufp = xmalloc (txtlen + 1);
      while (txtlen && p < pend)
        {
          for (n = *p++, txtlen--; txtlen && n && p < pend; txtlen--, n--)
            *bufp++ = *p++;
        }
      *bufp = 0;
      if (parse_txt_record (buffer, fpr))
        {
          xfree (buffer);
          return NULL;
        }
      return buffer;
    }

  return NULL;
}
