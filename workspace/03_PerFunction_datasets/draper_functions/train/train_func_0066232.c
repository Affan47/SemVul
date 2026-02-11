soap_getattrval(struct soap *soap, char *s, size_t n, soap_wchar d)
{ register size_t i;
  for (i = 0; i < n; i++)
  { register soap_wchar c = soap_get(soap);
    switch (c)
    {
    case SOAP_TT:
      *s++ = '<';
      soap_unget(soap, '/');
      break;
    case SOAP_LT:
      *s++ = '<';
      break;
    case SOAP_GT:
      if (d == ' ')
      { soap_unget(soap, c);
        *s = '\0';
        return SOAP_OK;
      }
      *s++ = '>';
      break;
    case SOAP_QT:
      if (c == d)
      { *s = '\0';
        return SOAP_OK;
      }
      *s++ = '"';
      break;
    case SOAP_AP:
      if (c == d)
      { *s = '\0';
        return SOAP_OK;
      }
      *s++ = '\'';
      break;
    case '\t':
    case '\n':
    case '\r':
    case ' ':
    case '/':
      if (d == ' ')
      { soap_unget(soap, c);
        *s = '\0';
        return SOAP_OK;
      }
    default:
      if ((int)c == EOF)
        return soap->error = SOAP_EOF;
      *s++ = (char)c;
    }
  }
  return soap->error = SOAP_EOM;
}
