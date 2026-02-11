reset(ResetMode mode)
	{
		if(c)
			c->reset();


		if(!server)
			issuerList.clear();

		state = Inactive;
		blocked = false;
		server = false;
		host = QString();
		sessionInfo = TLSContext::SessionInfo();
		actionTrigger.stop();
		op = -1;
		actionQueue.clear();
		need_update = false;
		maybe_input = false;
		emitted_hostNameReceived = false;
		emitted_certificateRequested = false;
		emitted_peerCertificateAvailable = false;

		out.clear();
		out_pending = 0;
		packet_out.clear();
		packet_out_pending = 0;

		if(mode >= ResetSessionAndData)
		{
			peerCert = CertificateChain();
			peerValidity = ErrorValidityUnknown;
			hostMismatch = false;
			errorCode = (TLS::Error)-1;

			in.clear();
			to_net.clear();
			from_net.clear();
			unprocessed.clear();
			to_net_encoded = 0;
			layer.reset();

			packet_in.clear();
			packet_to_net.clear();
			packet_from_net.clear();
			packet_to_net_encoded.clear();
		}

		if(mode >= ResetAll)
		{
			localCert = CertificateChain();
			localKey = PrivateKey();
			trusted = CertificateCollection();
			con_ssfMode = true;
			con_minSSF = 128;
			con_maxSSF = -1;
			con_cipherSuites = QStringList();
			tryCompress = false;
			packet_mtu = -1;
			issuerList.clear();
			session = TLSSession();
		}
	}
