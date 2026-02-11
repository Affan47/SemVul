constructNameDesc(CERTName * name)
{
  char * s;

  s = CERT_GetCommonName(name);
  if (s == 0) {
    s = CERT_GetOrgUnitName(name);
    if (s == 0) {
      s = CERT_GetOrgName(name);
      if (s == 0) {
        CERT_GetLocalityName(name);
        if (s == 0) {
          s = CERT_GetStateName(name);
          if (s == 0) s = "";
        }
      }
    }
  }

  return PORT_Strdup(s);
}
