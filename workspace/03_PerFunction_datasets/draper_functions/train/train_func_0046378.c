handle_host_error(XMPP::NameResolver::Error e)
{
#ifdef NETNAMES_DEBUG
	NNDEBUG << "e:" << e;
#endif


	cleanup_resolver(static_cast<XMPP::NameResolver*>(sender()));


	if (!lookup_host_fallback()) {

		handle_host_fallback_error(e);
	}
}
