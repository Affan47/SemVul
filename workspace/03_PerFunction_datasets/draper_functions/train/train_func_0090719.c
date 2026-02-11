ESInternalBaseFault(Arc::SOAPFault& fault,const std::string& message,const std::string& desc) {
  ESInternalBaseFault(fault.Detail(true).NewChild("dummy"),message,desc);
}
