flushSessionCache()
{
	poco_assert (_usage == SERVER_USE);

	Poco::Timestamp now;
	SSL_CTX_flush_sessions(_pSSLContext, static_cast<long>(now.epochTime()));
}
