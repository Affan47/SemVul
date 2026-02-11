rr_read(u_int16 RRTYPE, unsigned char*& RDATA, uint16_t &RDLEN, message_buff &buff, int ix, int len) {
  rr_type *info = rrtype_getinfo(RRTYPE);
  char *ptr;
  stl_string res;
  int x;
  _domain dom;

  if (ix + len > buff.len) throw PException("RR doesn't fit in DNS message");

  if (info) {

    try {
      ptr = info->properties;
      while (*ptr) {
        x = rr_len(*ptr, buff, ix, len);
        if (x > len) throw PException("RR item too long!");
        if (*ptr == 'd' || *ptr == 'm') {

          dom = dom_uncompress(buff, ix);
          res.append((char*)dom, domlen(dom));
          free(dom);
        } else {
          res.append((char*)buff.msg + ix, x);
        }

        ix += x;
        len -= x;

        ptr++;
      }
      if (len != 0) throw PException("extra data in RR");
    } catch(PException p) {
      throw PException("Parsing RR failed: ", p);
    }
    if (len != 0) throw PException("RR length too long");
  } else {

    res.append((char*)buff.msg + ix, len);
  }
  RDLEN = res.length();
  RDATA = (unsigned char *)memdup((void *)res.c_str(), res.length());
}
