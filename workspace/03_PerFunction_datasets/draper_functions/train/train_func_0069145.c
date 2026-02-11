soap_service_new(const char *urn, const char *method, SoapServiceFunc f)
{
  SoapService *service;


  service = (SoapService *) malloc(sizeof(SoapService));
  service->func = f;

  if (urn != NULL)
  {
    service->urn = (char *) malloc(strlen(urn) + 1);
    strcpy(service->urn, urn);
  }
  else
  {
    log_warn1("urn is NULL");
    service->urn = "";
  }

  if (method != NULL)
  {
    service->method = (char *) malloc(strlen(method) + 1);
    strcpy(service->method, method);
  }
  else
  {
    log_warn1("method is NULL");
    service->method = "";
  }

  return service;
}
