is_basetype(const char *prefix, const char *URI, const char *type)
{ const char *t = tname(prefix, URI, type);
  if (!strncmp(t, "enum ", 5))
    return true;
  if (strstr(t, "__") && strcmp(t, "xsd__byte"))
    return false;
  return !strncmp(type, "xs:", 3) || !strncmp(type, "SOAP-ENC:", 9);
}
