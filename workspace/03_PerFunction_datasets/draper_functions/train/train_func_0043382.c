attach(const StreamSocket& streamSocket)
{
	SecureStreamSocketImpl* pImpl = new SecureStreamSocketImpl(static_cast<StreamSocketImpl*>(streamSocket.impl()), SSLManager::instance().defaultClientContext());
	SecureStreamSocket result(pImpl);
	pImpl->connectSSL();
	return result;
}
