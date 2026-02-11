LC_Crypt_Token_VerifyPin(GWEN_CRYPT_TOKEN *ct,
                             LC_CARD *hcard,
                             GWEN_CRYPT_PINTYPE pt,
                             uint32_t guiid) {
  int rv;


  rv=LC_Crypt_Token__EnterPin(ct, hcard, pt, guiid);
  if (rv) {
    DBG_INFO(LC_LOGDOMAIN, "Error in pin input");
    return rv;
  }

  return 0;
}
