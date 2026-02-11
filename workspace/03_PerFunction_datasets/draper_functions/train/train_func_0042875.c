rr_torelstring(u_int16 RRTYPE, const unsigned char *_RDATA, int RDLENGTH, domainname zone) {
  rr_type *info = rrtype_getinfo(RRTYPE);
  char *ptr;
  const unsigned char *RDATA = _RDATA;
  stl_string ret;

  if (!info) return "<unknown rr type>";

  ptr = info->properties;
  while (*ptr) {
    if (ret != "") ret.append(" ");
    ret.append (rr_property_to_string (*ptr, RDATA, RDLENGTH - (int)(RDATA - _RDATA), zone));
    ptr++;
  }
  return ret;
}
