sql_literal_replace(const char *query,
                                  uint32 query_length,
                                  char *qry_buf,
                                  char *client_id)
{
  const char *s = query;
  char *ns = qry_buf;

#define COPY_NCHAR(to, from, num) \
  do {                            \
    *to++ = *from++;              \
  } while (--num > 0);            \

  while (*s != '\0' && (s - query) < query_length)
  {
    int rsl = 0;
    char expect = '\0';

    if ((rsl = is_numerics(s)))
    {
      s += rsl;
      *ns++ = '?';
    }
    else if ((rsl = is_edges_name_id(s)))
    {
      s += rsl;
      *ns++ = '?';
    }
    else if ((rsl = is_in_list(s, &expect)) ||
             (rsl = is_values_list(s, &expect)) ||
             (rsl = is_like_expr(s, &expect)))
    {
      COPY_NCHAR(ns, s, rsl);
      if (expect == '\0')
        expect = ' ';
      while (*s != expect && *s != SQL_TERM && (s - query) < query_length)
        ++s;
      *ns++ = '?';
    }
    else if (is_negative_numeric(s)) {
      s += 1;
      while (IS_NUMERIC(*s))
        ++s;
      *ns++ = '?';
    }
    else if ((rsl = is_comments(s, &expect)))
    {
      s += rsl;
      s += retrieve_client_id(s, client_id);
    }
    else if (*s == '\n' || *s == '\r')
    {
      *ns++ = ' ';
      ++s;
    }
    else {
      *ns++ = *s++;
    }
  }
  *ns = '\0';
  return ns - qry_buf;
}
