soap_array_begin_out(struct soap *soap, const char *tag, int id, const char *type, const char *offset)
{ if (!type || !*type)
    return soap_element_begin_out(soap, tag, id, NULL);
  if (soap_element(soap, tag, id, "SOAP-ENC:Array"))
    return soap->error;
  if (soap->version == 2)
  { const char *s;
    s = soap_strrchr(type, '[');
    if ((size_t)(s - type) < sizeof(soap->tmpbuf))
    { strncpy(soap->tmpbuf, type, s - type);
      soap->tmpbuf[s - type] = '\0';
      if (soap_attribute(soap, "SOAP-ENC:itemType", soap->tmpbuf))
        return soap->error;
      if (s && (soap_attribute(soap, "SOAP-ENC:arraySize", s + 1)))
        return soap->error;
    }
  }
  else
  { if (offset && soap_attribute(soap, "SOAP-ENC:offset", offset))
      return soap->error;
    if (soap_attribute(soap, "SOAP-ENC:arrayType", type))
      return soap->error;
  }
#ifndef WITH_LEAN
  if ((soap->mode & SOAP_XML_CANONICAL))
  { const char *s = strchr(type, ':');
    if (s)
      soap_utilize_ns(soap, type, s - type);
  }
#endif
  return soap_element_start_end_out(soap, NULL);
}
