VerifyCertificate()
{
	if (m_tlsState != handshake)
	{
		m_pOwner->LogMessage(::Debug_Warning, _T("VerifyCertificate called at wrong time"));
		return FZ_REPLY_ERROR;
	}

	m_tlsState = verifycert;

	if (gnutls_certificate_type_get(m_session) != GNUTLS_CRT_X509)
	{
		m_pOwner->LogMessage(::Error, _("Unsupported certificate type"));
		Failure(0, ECONNABORTED);
		return FZ_REPLY_ERROR;
	}

	unsigned int status = 0;
	if (gnutls_certificate_verify_peers2(m_session, &status) < 0)
	{
		m_pOwner->LogMessage(::Error, _("Failed to verify peer certificate"));
		Failure(0, ECONNABORTED);
		return FZ_REPLY_ERROR;
	}

	if (status & GNUTLS_CERT_REVOKED)
	{
		m_pOwner->LogMessage(::Error, _("Beware! Certificate has been revoked"));
		Failure(0, ECONNABORTED);
		return FZ_REPLY_ERROR;
	}

	if (status & GNUTLS_CERT_SIGNER_NOT_CA)
	{
		m_pOwner->LogMessage(::Error, _("Incomplete chain, top certificate is not self-signed certificate authority certificate"));
		Failure(0, ECONNABORTED);
		return FZ_REPLY_ERROR;
	}

	if (m_require_root_trust && status & GNUTLS_CERT_SIGNER_NOT_FOUND)
	{
		m_pOwner->LogMessage(::Error, _("Root certificate is not trusted"));
		Failure(0, ECONNABORTED);
		return FZ_REPLY_ERROR;
	}

	unsigned int cert_list_size;
	const gnutls_datum_t* cert_list = gnutls_certificate_get_peers(m_session, &cert_list_size);
	if (!cert_list || !cert_list_size)
	{
		m_pOwner->LogMessage(::Error, _("gnutls_certificate_get_peers returned no certificates"));
		Failure(0, ECONNABORTED);
		return FZ_REPLY_ERROR;
	}

	if (m_implicitTrustedCert.data)
	{
		if (m_implicitTrustedCert.size != cert_list[0].size ||
			memcmp(m_implicitTrustedCert.data, cert_list[0].data, cert_list[0].size))
		{
			m_pOwner->LogMessage(::Error, _("Primary connection and data connection certificates don't match."));
			Failure(0, ECONNABORTED);
			return FZ_REPLY_ERROR;
		}

		TrustCurrentCert(true);

		if (m_tlsState != conn)
			return FZ_REPLY_ERROR;
		return FZ_REPLY_OK;
	}

	std::vector<CCertificate> certificates;
	for (unsigned int i = 0; i < cert_list_size; i++)
	{
		CCertificate cert;
		if (ExtractCert(cert_list, cert))
			certificates.push_back(cert);
		else
		{
			Failure(0, ECONNABORTED);
			return FZ_REPLY_ERROR;
		}

		++cert_list;
	}

	CCertificateNotification *pNotification = new CCertificateNotification(
		m_pOwner->GetCurrentServer()->GetHost(),
		m_pOwner->GetCurrentServer()->GetPort(),
		GetProtocolName(),
		GetKeyExchange(),
		GetCipherName(),
		GetMacName(),
		certificates);

	m_pOwner->SendAsyncRequest(pNotification);

	m_pOwner->LogMessage(Status, _("Verifying certificate..."));

	return FZ_REPLY_WOULDBLOCK;
}
