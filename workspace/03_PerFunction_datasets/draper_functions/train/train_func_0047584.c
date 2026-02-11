Query(const UserConfig& uc, const Endpoint& cie, std::list<ComputingServiceType>& csList, const EndpointQueryOptions<ComputingServiceType>&) const {
    EndpointQueryingStatus s(EndpointQueryingStatus::FAILED);

    URL url(CreateURL(cie.URLString));
    if (!url) {
      return s;
    }

    logger.msg(DEBUG, "Collecting EMI-ES GLUE2 computing info endpoint information.");
    MCCConfig cfg;
    uc.ApplyToConfig(cfg);
    EMIESClient ac(url, cfg, uc.Timeout());
    XMLNode servicesQueryResponse;
    if (!ac.sstat(servicesQueryResponse)) {
      return s;
    }

    ExtractTargets(url, servicesQueryResponse, csList);

    for (std::list<ComputingServiceType>::iterator it = csList.begin(); it != csList.end(); it++) {
      (*it)->InformationOriginEndpoint = cie;
    }

    if (!csList.empty()) s = EndpointQueryingStatus::SUCCESSFUL;
    return s;
  }
