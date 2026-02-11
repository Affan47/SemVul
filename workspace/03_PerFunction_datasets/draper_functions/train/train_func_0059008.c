toEndpoint(const char* param) {

  IIOP::Address address;

  char* host = omniURI::extractHostPort(param, address.port);
  if (!host)
    return 0;

  if (*host == '\0') {

    const char* hostname = getenv(OMNIORB_USEHOSTNAME_VAR);
    if (hostname) {
      if (omniORB::trace(5)) {
	omniORB::logger log;
	log << "Use hostname '" << hostname << "' from "
	    << OMNIORB_USEHOSTNAME_VAR << " environment variable.\n";
      }
      address.host = hostname;
    }
    CORBA::string_free(host);
  }
  else {
    address.host = host;
  }
  return (giopEndpoint*)(new tcpEndpoint(address));
}
