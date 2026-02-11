submit(const std::string& jobdesc, std::string& jobid,
                          bool delegate) {
    action = "CreateActivity";
    logger.msg(VERBOSE, "Creating and sending submit request to %s", rurl.str());


    PayloadSOAP req(arex_ns);
    XMLNode op = req.NewChild("bes-factory:" + action);
    XMLNode act_doc = op.NewChild("bes-factory:ActivityDocument");
    WSAHeader(req).Action(BES_FACTORY_ACTIONS_BASE_URL + action);
    act_doc.NewChild(XMLNode(jobdesc));
    act_doc.Child(0).Namespaces(arex_ns);

    logger.msg(DEBUG, "Job description to be sent: %s", jobdesc);

    XMLNode response;
    if (!process(req, delegate, response))
      return false;

    XMLNode xmlJobId;
    response["ActivityIdentifier"].New(xmlJobId);
    xmlJobId.GetDoc(jobid);
    return true;
  }
