pname(bool flag, const char *prefix, const char *URI, const char *qname)
{ const char *r, *s = NULL, *t;
  t = cname(prefix, URI, qname);
  if (flag)
  { if (ptrtypemap.find(t) != ptrtypemap.end())
      s = ptrtypemap[t];
    else
    { if (usetypemap.find(t) != usetypemap.end())
        s = usetypemap[t];
      if (!s)
      { s = t;
        fprintf(stream, "\n// Warning: undefined QName '%s' for pointer to type '%s' (FIXME: check WSDL and schema definitions)\n", qname, t);
        if (vflag)
          fprintf(stderr, "\nWarning: undefined QName '%s' for pointer to type '%s' in namespace '%s'\n", qname, t, URI?URI:"?");
      }
      r = s;
      while (r && *r)
      { r = strchr(r + 1, '*');
        if (r && *(r-1) != '/' && *(r+1) != '/')
          break;
      }
      if (!r)
      { char *p = (char*)emalloc(strlen(s) + 2);
        strcpy(p, s);
        strcat(p, "*");
        s = p;
      }
      if (vflag)
        cerr << "Mapping pointer to '" << t << "' to '" << s << "'" << endl;
      ptrtypemap[t] = s;
    }
  }
  else if (usetypemap.find(t) != usetypemap.end())
    s = usetypemap[t];
  else
  { s = t;
    fprintf(stream, "\n// Warning: undefined QName '%s' for type '%s' in namespace '%s' (FIXME: check WSDL and schema definitions)\n", qname, t, URI?URI:"?");
    if (vflag)
      fprintf(stderr, "\nWarning: undefined QName '%s' for type '%s' in namespace '%s'\n", qname, t, URI?URI:"?");
  }
  return s;
}
