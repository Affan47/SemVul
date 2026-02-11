setPublicKey(const CACertificate* pCert)
	{
		if(pCert==NULL)
			return E_UNKNOWN;
		EVP_PKEY* pubkey=X509_get_pubkey(pCert->m_pCert);
		if(pubkey==NULL||(pubkey->type!=EVP_PKEY_RSA&&pubkey->type!=EVP_PKEY_RSA2))
			return E_UNKNOWN;
		RSA* r=pubkey->pkey.rsa;
		if(RSA_size(r)!=128)
			return E_UNKNOWN;
		if(m_pRSA!=NULL)
			RSA_free(m_pRSA);
		m_pRSA=r;
		setRSAFlags(m_pRSA);
		return E_SUCCESS;
	}
