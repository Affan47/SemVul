publish_one(const char*    	     publish_spec,
	    const char*    	     ep,
	    CORBA::Boolean 	     no_publish,
	    orbServer::EndpointList& published_eps)
{
  OMNIORB_ASSERT(!strncmp(ep, "giop:unix:", 10));

  CORBA::String_var to_add;

  if (!strncmp(publish_spec, "giop:unix:", 10)) {
    const char* file = publish_spec + 10;
    if (strlen(file) == 0)
      to_add = ep;
    else
      to_add = publish_spec;
  }
  else if (no_publish) {

    return 0;
  }
  else if (omni::strMatch(publish_spec, "addr")) {
    to_add = ep;
  }
  else {

    return 0;
  }

  if (!omniObjAdapter::endpointInList(to_add, published_eps)) {
    if (omniORB::trace(20)) {
      omniORB::logger l;
      l << "Publish endpoint '" << to_add << "'\n";
    }
    giopEndpoint::addToIOR(to_add);
    published_eps.length(published_eps.length() + 1);
    published_eps[published_eps.length() - 1] = to_add._retn();
  }
  return 1;
}
