fetch_uri (Sess *sess, Sess_Private_Data *priv, Call_Private_Data *cpriv,
	   const char *uri, size_t uri_len)
{
  struct uri_list *el;
  int is_relative;
  size_t len;
  char *dst;

  if (strchr (uri, ':'))
    {
      len = strlen (param.server);
      if (strncmp (uri, "http://", 7) == 0
	  && strncmp (uri + 7, param.server, len) == 0
	  && uri[7 + len] == '/')
	{
	  uri += 7 + len;
	  uri_len -= 7 + len;
	}
      else
	{


	  if (verbose > 1)
	    fprintf (stderr, "%s: ignoring absolute URI `%s'\n",
		     prog_name, uri);
	  return;
	}
    }

  is_relative = (uri[0] != '/');


  len = uri_len;
  if (is_relative)
    len += prefix_len;
  el = malloc (sizeof (*el) + len);
  if (!el)
    panic ("%s.fetch_uri: out of memory!\n", prog_name);

  el->uri_len = len;
  dst = el->uri;
  if (is_relative)
    {
      memcpy (el->uri, prefix, prefix_len);
      dst += prefix_len;
    }
  memcpy (dst, uri, uri_len + 1);

  el->next = priv->uri_list;
  priv->uri_list = el;

  issue_calls (sess, priv);
}
