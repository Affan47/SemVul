soap_sender_fault_subcode(struct soap *soap, const char *faultsubcodeQName, const char *faultstring, const char *faultdetailXML)
{ return soap_copy_fault(soap, soap->version == 2 ? "SOAP-ENV:Sender" : "SOAP-ENV:Client", faultsubcodeQName, faultstring, faultdetailXML);
}
