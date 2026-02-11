set(const JobDescription& _j) const {
    BrokerPlugin::set(_j);
    if (j) {
      uc.ApplyToConfig(cfg);
      if (request) {
        delete request;
      }
      Arc::NS ns("a-rex", "http://www.nordugrid.org/schemas/a-rex");
      request = new PayloadSOAP(ns);
      XMLNode req = request->NewChild("a-rex:CacheCheck").NewChild("a-rex:TheseFilesNeedToCheck");

      for (std::list<InputFileType>::const_iterator it = j->DataStaging.InputFiles.begin();
           it != j->DataStaging.InputFiles.end(); ++it) {
        if (!it->Sources.empty()) {
          req.NewChild("a-rex:FileURL") = it->Sources.front().fullstr();
        }
      }
    }
  }
