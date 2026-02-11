soap_s2xsd__duration(struct soap *soap, const char *s, LONG64 *a)
{ LONG64 sign = 1, Y = 0, M = 0, D = 0, H = 0, N = 0, S = 0;
  float f = 0;
  *a = 0;
  if (s)
  { if (*s == '-')
    { sign = -1;
      s++;
    }
    if (*s++ != 'P')
      return soap->error = SOAP_TYPE;

    while (s && *s)
    { LONG64 n;
      char k;
      if (*s == 'T')
      { s++;
	break;
      }
      if (sscanf(s, SOAP_LONG_FORMAT"%c", &n, &k) != 2)
	return soap->error = SOAP_TYPE;
      s = strchr(s, k);
      if (!s)
	return soap->error = SOAP_TYPE;
      switch (k)
      { case 'Y':
	  Y = n;
	  break;
	case 'M':
	  M = n;
	  break;
	case 'D':
	  D = n;
	  break;
	default:
	  return soap->error = SOAP_TYPE;
      }
      s++;
    }

    while (s && *s)
    { LONG64 n;
      char k;
      if (sscanf(s, SOAP_LONG_FORMAT"%c", &n, &k) != 2)
	return soap->error = SOAP_TYPE;
      s = strchr(s, k);
      if (!s)
	return soap->error = SOAP_TYPE;
      switch (k)
      { case 'H':
	  H = n;
	  break;
	case 'M':
	  N = n;
	  break;
	case '.':
	  S = n;
	  if (sscanf(s, "%g", &f) != 1)
	    return soap->error = SOAP_TYPE;
	  s = NULL;
	  continue;
	case 'S':
	  S = n;
	  break;
	default:
	  return soap->error = SOAP_TYPE;
      }
      s++;
    }

    *a = sign * ((((((((((((Y * 12) + M) * 30) + D) * 24) + H) * 60) + N) * 60) + S) * 1000) + (long)(1000.0 * f));
  }
  return soap->error;
}
