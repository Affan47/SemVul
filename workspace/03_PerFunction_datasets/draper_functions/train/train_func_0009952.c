EBC_Provider_ResultCodeToLogLevel(GWEN_UNUSED AB_PROVIDER *pro,
						    const char *s) {
  if (strlen(s)!=6) {
    DBG_ERROR(AQEBICS_LOGDOMAIN, "Invalid error code [%s]", s);
    return GWEN_LoggerLevel_Error;
  }
  else {
    uint8_t c;
    GWEN_LOGGER_LEVEL lev;

    c=s[1]-'0';
    switch(c) {
    case 0:  lev=GWEN_LoggerLevel_Info; break;
    case 1:  lev=GWEN_LoggerLevel_Notice; break;
    case 3:  lev=GWEN_LoggerLevel_Warning; break;
    case 6:
    case 9:
    default: lev=GWEN_LoggerLevel_Error; break;
    }

    return lev;
  }
}
