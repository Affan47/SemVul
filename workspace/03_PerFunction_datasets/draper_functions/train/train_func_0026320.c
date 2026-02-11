x509_load_serial(const std::string& CAfile, const std::string& serialfile) {
    ASN1_INTEGER *bs = NULL;
    BIGNUM *serial = NULL;

    std::string serial_f;
    if(!serialfile.empty()) serial_f = serialfile;
    else if(!CAfile.empty()){
      std::size_t pos; pos = CAfile.rfind(".");
      if(pos != std::string::npos) serial_f = CAfile.substr(0, pos);
      serial_f.append(".srl");
    }
    else{ return bs;}

    serial = load_serial(serial_f, NULL);
    if (serial == NULL) {
      CredentialLogger.msg(ERROR,"load serial from %s failure",serial_f.c_str());
      return bs;
    }

    if (!BN_add_word(serial,1)) {
      CredentialLogger.msg(ERROR,"add_word failure");
      BN_free(serial); return bs;
    }

    if(!save_serial(serial_f, NULL, serial, &bs)) {
      CredentialLogger.msg(ERROR,"save serial to %s failure",serial_f.c_str());
      BN_free(serial); return bs;
    }
    BN_free(serial);
    return bs;
  }
