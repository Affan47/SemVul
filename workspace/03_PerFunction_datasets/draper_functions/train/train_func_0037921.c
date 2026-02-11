handleError(int rc)
{
	if (rc > 0) return rc;

	int sslError = SSL_get_error(_pSSL, rc);
	switch (sslError)
	{
	case SSL_ERROR_ZERO_RETURN:
		return 0;
	case SSL_ERROR_WANT_READ:
		return SecureStreamSocket::ERR_SSL_WANT_READ;
	case SSL_ERROR_WANT_WRITE:
		return SecureStreamSocket::ERR_SSL_WANT_WRITE;
	case SSL_ERROR_WANT_CONNECT:
	case SSL_ERROR_WANT_ACCEPT:
	case SSL_ERROR_WANT_X509_LOOKUP:

		poco_bugcheck();
		return rc;
	default:
		{
			long lastError = ERR_get_error();
			if (lastError == 0)
			{
				if (rc == 0)
				{
					throw SSLConnectionUnexpectedlyClosedException();
				}
				else
				{
					SecureStreamSocketImpl::error(Poco::format("The BIO reported an error: %d", rc));
				}
			}
			else
			{
				char buffer[256];
				ERR_error_string_n(lastError, buffer, sizeof(buffer));
				std::string msg(buffer);
				throw SSLException(msg);
			}
		}
 		break;
	}
	return rc;
}
