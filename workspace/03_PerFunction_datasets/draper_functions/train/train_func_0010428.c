match(const ExecutionTarget& et) const {
    if(!BrokerPlugin::match(et)) return false;

    if (et.ComputingEndpoint->Implementation < Software("ARC", "1")) {
      return false;
    }

    if (!request) {
      return false;
    }

    std::map<std::string, long>::iterator it = CacheMappingTable.insert(std::pair<std::string, long>(et.ComputingEndpoint->URLString, 0)).first;

    PayloadSOAP *response = NULL;
    URL url(et.ComputingEndpoint->URLString);
    ClientSOAP client(cfg, url, uc.Timeout());
    if (!client.process(request, &response)) {
      return true;
    }
    if (response == NULL) {
      return true;
    }

    for (XMLNode ExistCount = (*response)["CacheCheckResponse"]["CacheCheckResult"]["Result"];
         (bool)ExistCount; ++ExistCount) {
      it->second += stringto<long>((std::string)ExistCount["FileSize"]);
    }

    delete response;
    return true;
  }
