ensureType(SecureMessageKey::Type t)
	{

		if(type != SecureMessageKey::None && t != type)
		{
			if(type == SecureMessageKey::X509)
			{
				cert_pub = CertificateChain();
				cert_sec = PrivateKey();
			}
			else if(type == SecureMessageKey::PGP)
			{
				pgp_pub = PGPKey();
				pgp_sec = PGPKey();
			}
		}
		type = t;
	}
