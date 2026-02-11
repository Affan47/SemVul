get_key_from_certstr(const std::string& value) {
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

  xmlSecErrorsDefaultCallbackEnableOutput(FALSE);

  BIO* certbio = NULL;
  std::string cert_value;

  cert_value.append("-----BEGIN CERTIFICATE-----").append("\n").append(value).append("\n").append("-----END CERTIFICATE-----"
);

  for (int i=0; key_formats[i] && key == NULL; i++) {
    certbio = BIO_new_mem_buf((void*)(cert_value.c_str()), cert_value.size());
    key = xmlSecOpenSSLAppKeyFromCertLoadBIO(certbio, key_formats[i]);
    BIO_free(certbio);
    if(key != NULL) break;
    unsigned long e = ERR_get_error();
    while(e != SSL_ERROR_NONE) {
      e = ERR_get_error();
    }
  }

  xmlSecErrorsDefaultCallbackEnableOutput(TRUE);

  return key;
}
