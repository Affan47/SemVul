tname(const char *prefix, const char *URI, const char *qname)
{ const char *s, *t;
  t = cname(prefix, URI, qname);
  if (usetypemap.find(t) != usetypemap.end())
  { s = usetypemap[t];
    if (vflag)
      cerr << "Mapping use of '" << t << "' to '" << s << "'" << endl;
  }
  else
  { s = t;
    fprintf(stream, "\n// Warning: undefined QName '%s' for type '%s' in namespace '%s' (FIXME: check WSDL and schema definitions)\n", qname?qname:"", t, URI?URI:"?");
    if (vflag)
      fprintf(stderr, "\nWarning: undefined QName '%s' for type '%s' in namespace '%s'\n", qname?qname:"", t, URI?URI:"?");
  }
  return s;
}
