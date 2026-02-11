addEntity(const ComputingServiceType& service) {
    if (!service->ID.empty()) {

      for(std::list<ComputingServiceType>::iterator it = services.begin(); it != services.end(); it++) {

        if ((*it)->ID == service->ID) {
          std::map<std::string, int> priority;
          priority["org.nordugrid.ldapglue2"] = 3;
          priority["org.ogf.glue.emies.resourceinfo"] = 2;
          priority["org.nordugrid.wsrfglue2"] = 1;

          if (priority[service->InformationOriginEndpoint.InterfaceName] > priority[(*it)->InformationOriginEndpoint.InterfaceName]) {
            logger.msg(DEBUG, "Uniq is replacing service coming from %s with service coming from %s", (*it)->InformationOriginEndpoint.str(), service->InformationOriginEndpoint.str());
            (*it) = service;
            return;
          } else {
            logger.msg(DEBUG, "Uniq is ignoring service coming from %s", service->InformationOriginEndpoint.str());
            return;
          }
        }
      }
    }

    logger.msg(DEBUG, "Uniq is adding service coming from %s", service->InformationOriginEndpoint.str());
    services.push_back(service);
  }
