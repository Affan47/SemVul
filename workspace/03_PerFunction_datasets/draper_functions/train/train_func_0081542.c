RequestedProperties(bool create) {
  SOAPFault* fault = soap_.Fault();
  if(!fault) return XMLNode();
  XMLNode detail = fault->Detail(true);
  XMLNode failure = detail["wsrf-rp:ResourcePropertyChangeFailure"];
  if(!failure) {
    if(!create) return XMLNode();
    failure=detail.NewChild("wsrf-rp:ResourcePropertyChangeFailure");
  };
  XMLNode req_value = failure["wsrf-rp:RequestedValue"];
  if(!req_value) {
    if(!create) return XMLNode();
    req_value=failure.NewChild("wsrf-rp:RequestedValue");
  };
  return req_value;
}
