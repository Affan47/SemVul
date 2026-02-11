AddDN(const std::string& dn) {
    XMLNode pdp = operator[]("PDP");
    pdp.NewChild("DN") = dn;
  }
