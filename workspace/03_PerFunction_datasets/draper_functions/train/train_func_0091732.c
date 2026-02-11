make_raw_fault(Message& outmsg,const char* = NULL)
{
  NS ns;
  SOAPEnvelope soap(ns,true);
  soap.Fault()->Code(SOAPFault::Receiver);
  std::string xml; soap.GetXML(xml);
  PayloadRaw* payload = new PayloadRaw;
  payload->Insert(xml.c_str());
  outmsg.Payload(payload);
  return MCC_Status(GENERIC_ERROR);
}
