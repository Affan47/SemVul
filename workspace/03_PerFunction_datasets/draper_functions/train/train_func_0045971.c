soap_match_array(struct soap *soap, const char *type)
{ if (*soap->arrayType)
    if (soap_match_tag(soap, soap->arrayType, type)
     && soap_match_tag(soap, soap->arrayType, "xsd:anyType")
     && soap_match_tag(soap, soap->arrayType, "xsd:ur-type")
    )
    { DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Array type mismatch: '%s' '%s'\n", soap->arrayType, type));
      return SOAP_TAG_MISMATCH;
    }
  return SOAP_OK;
}
