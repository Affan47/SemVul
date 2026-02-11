reconnect(void) {
    delete client; client = NULL;
    logger.msg(DEBUG, "Re-creating an EMI ES client");
    client = new ClientSOAP(cfg, rurl, timeout);
    if (!client) {
      lfailure = "Unable to create SOAP client used by EMIESClient.";
      return false;
    }
    set_namespaces(ns);
    return true;
  }
