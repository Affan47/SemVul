GetGlobalID(Arc::XMLNode& pnode) {
    Arc::XMLNode node;
    if(!pnode) {
      Arc::NS ns;
      ns["estypes"]="http://www.eu-emi.eu/es/2010/12/types";
      Arc::XMLNode(ns,"estypes:ActivityID").Exchange(pnode);
      node = pnode;
    } else {
      node = pnode.NewChild("estypes:ActivityID");
    };
    node = id_;
    return node;
  }
