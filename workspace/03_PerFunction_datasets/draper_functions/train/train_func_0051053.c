soap_s2short(struct soap *soap, const char *s, short *p)
{ if (s)
  { long n;
    char *r;
    n = soap_strtol(s, &r, 10);
    if (s == r || *r || n < -32768 || n > 32767)
      soap->error = SOAP_TYPE;
    *p = (short)n;
  }
  return soap->error;
}
