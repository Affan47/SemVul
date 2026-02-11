soap_env_new_with_fault(fault_code_t faultcode,
                        const char *faultstring,
                        const char *faultactor, const char *detail,
                        SoapEnv ** out)
{
  xmlDocPtr doc;
  herror_t err;

  doc = soap_fault_build(faultcode, faultstring, faultactor, detail);
  if (doc == NULL)
    return herror_new("soap_env_new_with_fault",
                      XML_ERROR_PARSE, "Can not parse fault xml");

  if ((err = soap_env_new_from_doc(doc, out)) != H_OK)
  {
    xmlFreeDoc(doc);
  }

  return err;
}
