havePeerCertificate() const
{
	X509* pCert = _impl.peerCertificate();
	if (pCert)
	{
		X509_free(pCert);
		return true;
	}
	else return false;
}
