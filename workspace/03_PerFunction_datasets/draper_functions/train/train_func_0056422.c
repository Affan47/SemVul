entitize(const char * str, int is_html)
{
  int elen, ecount, nsecount;
  entity_types *ep;
  const char * cp;
  char * p, * tmp, * xstr;

  int bytes = 0;
  int value = 0;
  ep = stdentities;
  elen = ecount = nsecount = 0;


  while (ep->text) {
    cp = str;
    while ((cp = strstr(cp, ep->text)) != NULL) {
      elen += strlen(ep->entity) - strlen(ep->text);
      ecount++;
      cp += strlen(ep->text);
    }
    ep++;
  }


#if 0
  for (cp = str; *cp; cp++) {
    if (*cp & 0x80) {
      cet_utf8_to_ucs4(cp, &bytes, &value);
      cp += bytes-1;
      elen += sprintf(tmpsub, "&#x%x;", value) - bytes;
      nsecount++;
    }
  }
#endif


  tmp = (char *) xcalloc((strlen(str) + elen + 1), 1);
  strcpy(tmp, str);


  if (ecount == 0 && nsecount == 0) {
    return (tmp);
  }

  if (ecount != 0) {
    for (ep = stdentities; ep->text; ep++) {
      p = tmp;
      if (is_html && ep->not_html)  {
        continue;
      }
      while ((p = strstr(p, ep->text)) != NULL) {
        elen = strlen(ep->entity);

        xstr = xstrdup(p + strlen(ep->text));

        strcpy(p, ep->entity);
        strcpy(p + elen, xstr);

        xfree(xstr);

        p += elen;
      }
    }
  }

  if (nsecount != 0) {
    p = tmp;
    while (*p) {
      if (*p & 0x80) {
        cet_utf8_to_ucs4(p, &bytes, &value);
        if (p[bytes]) {
          xstr = xstrdup(p + bytes);
        } else {
          xstr = NULL;
        }
        sprintf(p, "&#x%x;", value);
        p = p+strlen(p);
        if (xstr) {
          strcpy(p, xstr);
          xfree(xstr);
        }
      } else {
        p++;
      }
    }
  }
  return (tmp);
}
