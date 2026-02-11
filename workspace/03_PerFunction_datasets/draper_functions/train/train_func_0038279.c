setBiDirServiceContext(omniInterceptors::clientSendRequest_T::info_T& info) {

  if (!orbParameters::offerBiDirectionalGIOP) {


    return 1;
  }

  giopStrand& g = (giopStrand&)info.giop_c;
  GIOP::Version ver = info.giop_c.version();

  if (ver.minor != 2 || !g.biDir || !g.isClient() || g.biDir_initiated) {


    return 1;
  }

  const orbServer::EndpointList& epts = omniObjAdapter::listMyEndpoints();
  CORBA::ULong el = epts.length();

  ListenPointList l(el);
  CORBA::ULong j = 0;

  for (CORBA::ULong i=0 ; i != el; i++) {
    const char* ep = epts[i];
    if (strncmp(ep,"giop:tcp:",9) == 0 || strncmp(ep,"giop:ssl:",9) == 0) {
      l.length(j+1);
      if (!tcpTransportImpl::parseAddress(ep+9, l[j++])) OMNIORB_ASSERT(0);
    }
  }
  if (l.length()) {
    cdrEncapsulationStream e(CORBA::ULong(0),CORBA::Boolean(1));
    l >>= e;

    CORBA::Octet* data;
    CORBA::ULong max,datalen;
    e.getOctetStream(data,max,datalen);

    CORBA::ULong len = info.service_contexts.length() + 1;
    info.service_contexts.length(len);
    info.service_contexts[len-1].context_id = IOP::BI_DIR_IIOP;
    info.service_contexts[len-1].context_data.replace(max,datalen,data,1);

    if (omniORB::trace(25)) {
      omniORB::logger log;
      log << "Send bidir IIOP service context: ( ";

      for (CORBA::ULong i = 0; i < l.length(); i++) {
	log << (const char*) l[i].host << ":" << l[i].port << " ";
      }

      log << ")\n";
    }
  }
  g.biDir_initiated = 1;
  return 1;
}
