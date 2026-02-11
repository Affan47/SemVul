deleteStrandAndConnection(CORBA::Boolean forced)
{

  CORBA::String_var peeraddr;

  if (connection) {

    peeraddr = connection->peeraddress();

    int count;
    if (!forced) {
      count = connection->decrRefCount();
      if (omniORB::trace(25)) {
	omniORB::logger log;
	log << (isClient() ? "Client" : "Server")
	    << " connection refcount = " << count << "\n";
      }
      OMNIORB_ASSERT(count >= 0);
      if (count != 0)
	return;
    }
    else {
      count = connection->decrRefCount(1);
      if (omniORB::trace(25)) {
	omniORB::logger log;
	log << (isClient() ? "Client" : "Server")
	    << " connection refcount (forced) = " << count << "\n";
      }
      if (count) {


	OMNIORB_ASSERT(biDir);
	connection->Shutdown();

	return;

      }
    }
  }
  if (omniORB::trace(20) && connection) {
    omniORB::logger log;
    log << (isClient() ? "Client" : "Server")
	<< " close connection"
	<< (isClient() ? " to " : " from ")
	<< (const char*)peeraddr << "\n";
  }
  pd_state = DYING;
  delete this;
}
