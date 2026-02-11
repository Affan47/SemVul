same_questions(const unsigned char *qbuf, int qlen,
                          const unsigned char *abuf, int alen)
{
  struct {
    const unsigned char *p;
    int qdcount;
    char *name;
    long namelen;
    int type;
    int dnsclass;
  } q, a;
  int i, j;

  if (qlen < HFIXEDSZ || alen < HFIXEDSZ)
    return 0;


  q.qdcount = DNS_HEADER_QDCOUNT(qbuf);
  a.qdcount = DNS_HEADER_QDCOUNT(abuf);
  if (q.qdcount != a.qdcount)
    return 0;


  q.p = qbuf + HFIXEDSZ;
  for (i = 0; i < q.qdcount; i++)
    {

      if (ares_expand_name(q.p, qbuf, qlen, &q.name, &q.namelen)
          != ARES_SUCCESS)
        return 0;
      q.p += q.namelen;
      if (q.p + QFIXEDSZ > qbuf + qlen)
        {
          free(q.name);
          return 0;
        }
      q.type = DNS_QUESTION_TYPE(q.p);
      q.dnsclass = DNS_QUESTION_CLASS(q.p);
      q.p += QFIXEDSZ;


      a.p = abuf + HFIXEDSZ;
      for (j = 0; j < a.qdcount; j++)
        {

          if (ares_expand_name(a.p, abuf, alen, &a.name, &a.namelen)
              != ARES_SUCCESS)
            {
              free(q.name);
              return 0;
            }
          a.p += a.namelen;
          if (a.p + QFIXEDSZ > abuf + alen)
            {
              free(q.name);
              free(a.name);
              return 0;
            }
          a.type = DNS_QUESTION_TYPE(a.p);
          a.dnsclass = DNS_QUESTION_CLASS(a.p);
          a.p += QFIXEDSZ;


          if (strcasecmp(q.name, a.name) == 0 && q.type == a.type
              && q.dnsclass == a.dnsclass)
            {
              free(a.name);
              break;
            }
          free(a.name);
        }

      free(q.name);
      if (j == a.qdcount)
        return 0;
    }
  return 1;
}
