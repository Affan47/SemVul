LC_Crypt_Token_VerifyPinWithPinInfo(GWEN_CRYPT_TOKEN *ct,
                                        LC_CARD *hcard,
                                        GWEN_CRYPT_PINTYPE pt,
                                        const LC_PININFO *pi,
                                        uint32_t guiid) {
  int rv;


  rv=LC_Crypt_Token__EnterPinWithPinInfo(ct, hcard, pt, pi, guiid);
  if (rv) {
    DBG_INFO(LC_LOGDOMAIN, "Error in pin input");
    return rv;
  }

  return 0;
}
