sstat(XMLNode& response, bool nsapply) {


    std::string action = "GetResourceInfo";
    logger.msg(VERBOSE, "Creating and sending service information request to %s", rurl.str());

    PayloadSOAP req(ns);
    XMLNode op = req.NewChild("esrinfo:" + action);
    XMLNode res;

    if (!process(req, res)) return false;

    if(nsapply) res.Namespaces(ns);
    XMLNode services = res["Services"];
    if(!services) {
      lfailure = "Missing Services in response";
      return false;
    }
    services.Move(response);


    return true;
  }
