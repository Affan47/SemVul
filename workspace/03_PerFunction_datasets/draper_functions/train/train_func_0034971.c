get_key_from_keystr(const std::string& value) {
  xmlSecKey *key = NULL;
  xmlSecKeyDataFormat key_formats[] = {
    xmlSecKeyDataFormatDer,
    xmlSecKeyDataFormatCertDer,
    xmlSecKeyDataFormatPkcs8Der,
    xmlSecKeyDataFormatCertPem,
    xmlSecKeyDataFormatPkcs8Pem,
    xmlSecKeyDataFormatPem,
    xmlSecKeyDataFormatBinary,
    (xmlSecKeyDataFormat)0
  };

  int rc;


  std::string v;
  std::size_t pos1, pos2;
  pos1 = value.find("BEGIN RSA PRIVATE KEY");
  if(pos1 == std::string::npos) {
    pos1 = value.find("BEGIN RSA PUBLIC KEY");
  }
  if(pos1 != std::string::npos) {
    pos1 = pos1 + 21;
    pos2 = value.find_first_not_of("-", pos1);
    v = value.substr(pos2);
    pos2 = v.find_first_of("-");
    v.resize(pos2);
  }
  else v = value;

  xmlSecErrorsDefaultCallbackEnableOutput(FALSE);
  xmlSecByte* tmp_str = new xmlSecByte[v.size()];
  memset(tmp_str,0,v.size());

  rc = xmlSecBase64Decode((const xmlChar*)(v.c_str()), tmp_str, v.size());
  if (rc < 0) {

    memcpy(tmp_str,v.c_str(),v.size());
    rc = v.size();
  }
  for (int i=0; key_formats[i] && key == NULL; i++) {
    key = xmlSecCryptoAppKeyLoadMemory(tmp_str, rc, key_formats[i], NULL, NULL, NULL);
  }
  delete[] tmp_str;
  xmlSecErrorsDefaultCallbackEnableOutput(TRUE);

  return key;
}
