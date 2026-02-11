checkEncryption(GooString *ownerPassword, GooString *userPassword) {
  Object encrypt;
  GBool encrypted;
  SecurityHandler *secHdlr;
  GBool ret;

  xref->getTrailerDict()->dictLookup("Encrypt", &encrypt);
  if ((encrypted = encrypt.isDict())) {
    if ((secHdlr = SecurityHandler::make(this, &encrypt))) {
      if (secHdlr->checkEncryption(ownerPassword, userPassword)) {

       	xref->setEncryption(secHdlr->getPermissionFlags(),
			    secHdlr->getOwnerPasswordOk(),
			    secHdlr->getFileKey(),
			    secHdlr->getFileKeyLength(),
			    secHdlr->getEncVersion(),
			    secHdlr->getEncRevision(),
			    secHdlr->getEncAlgorithm());
	ret = gTrue;
      } else {

	ret = gFalse;
      }
      delete secHdlr;
    } else {

      ret = gFalse;
    }
  } else {

    ret = gTrue;
  }
  encrypt.free();
  return ret;
}
