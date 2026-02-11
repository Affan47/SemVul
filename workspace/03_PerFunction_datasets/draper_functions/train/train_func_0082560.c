match(const char* sendfrom,
		       const giopAddressList& addrlist) const {

  if (!omni::strMatch(pd_sendfrom,sendfrom)) return 0;

  giopAddressList::const_iterator i, last;
  i    = addrlist.begin();
  last = addrlist.end();
  for (; i != last; i++) {
    giopAddressList::const_iterator j, k;
    j = pd_redirect_addresses.begin();
    k = pd_redirect_addresses.end();
    for (; j != k; j++) {
      if (omni::ptrStrMatch((*i)->address(),(*j)->address())) return 1;
    }
  }
  return 0;
}
