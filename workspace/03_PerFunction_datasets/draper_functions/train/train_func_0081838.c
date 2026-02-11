make_raw_fault(Message& outmsg,const char* desc = NULL) {
  PayloadRaw* outpayload = new PayloadRaw;
  if(desc) outpayload->Insert(desc,0);
  outmsg.Payload(outpayload);
  if(desc) return MCC_Status(GENERIC_ERROR,"HTTP",desc);
  return MCC_Status(GENERIC_ERROR,"HTTP");
}
