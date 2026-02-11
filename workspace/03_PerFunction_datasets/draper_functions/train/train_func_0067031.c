soap_router_find_service(SoapRouter * router,
                         const char *urn, const char *method)
{
  SoapServiceNode *node;

  if (router == NULL || urn == NULL || method == NULL)
    return NULL;

  node = router->service_head;

  while (node)
  {
    if (node->service && node->service->urn && node->service->method)
    {

      if (!strcmp(node->service->urn, urn)
          && !strcmp(node->service->method, method))
        return node->service;

    }

    node = node->next;
  }

  return router->default_service;
}
