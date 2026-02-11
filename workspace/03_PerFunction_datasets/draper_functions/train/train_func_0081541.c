AH_User_Flags_fromDb(GWEN_DB_NODE *db, const char *name) {
  uint32_t fl=0;
  int i;

  for (i=0; ; i++) {
    const char *s;

    s=GWEN_DB_GetCharValue(db, name, i, 0);
    if (!s)
      break;
    if (strcasecmp(s, "bankDoesntSign")==0)
      fl|=AH_USER_FLAGS_BANK_DOESNT_SIGN;
    else if (strcasecmp(s, "bankUsesSignSeq")==0)
      fl|=AH_USER_FLAGS_BANK_USES_SIGNSEQ;
    else if (strcasecmp(s, "keepAlive")==0)
      fl|=AH_USER_FLAGS_KEEPALIVE;
    else if (strcasecmp(s, "ignoreUpd")==0)
      fl|=AH_USER_FLAGS_IGNORE_UPD;
    else if (strcasecmp(s, "forceSsl3")==0 ||
	     strcasecmp(s, "forceSslv3")==0)
      fl|=AH_USER_FLAGS_FORCE_SSL3;
    else if (strcasecmp(s, "noBase64")==0)
      fl|=AH_USER_FLAGS_NO_BASE64;
    else if (strcasecmp(s, "keepMultipleBlanks")==0)
      fl|=AH_USER_FLAGS_KEEP_MULTIPLE_BLANKS;
    else if (strcasecmp(s, "omitSmsAccount")==0)
      fl|=AH_USER_FLAGS_TAN_OMIT_SMS_ACCOUNT;
    else if (strcasecmp(s, "tlsOnlySafeCiphers")==0)
      fl|=AH_USER_FLAGS_TLS_ONLY_SAFE_CIPHERS;
    else {
      DBG_WARN(AQHBCI_LOGDOMAIN, "Unknown user flag \"%s\"", s);
    }
  }

  return fl;
}
