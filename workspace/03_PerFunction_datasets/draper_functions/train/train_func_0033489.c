write_section(stl_list(DnsRR)& section, int lenpos, stl_string& message, stl_slist(dom_compr_info) &comprinfo, int maxlen, bool is_additional) {
  stl_list(DnsRR)::iterator it = section.begin();

  int n = 0, x;

  x = message.size();

  while (it != section.end()) {
    write_rr(*it, message, &comprinfo, (OPCODE == OPCODE_UPDATE) ? 1 : 0);
    if (maxlen != -1 && message.size() > (unsigned)maxlen) {

      message.resize(x);
      if (!is_additional) message[2] |= 2;
      message[lenpos] = n / 256;
      message[lenpos + 1] = n;
      throw PTruncatedException();
    }
    x = message.size();
    it++;
    n++;
  }


  message[lenpos] = n / 256;
  message[lenpos + 1] = n;
}
