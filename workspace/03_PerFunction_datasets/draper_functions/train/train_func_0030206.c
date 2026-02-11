VerifyIdent(CClientCredits* pTarget, const byte* pachSignature, uint8 nInputSize, uint32 dwForIP, uint8 byChaIPKind)
{
	wxASSERT( pTarget );
	wxASSERT( pachSignature );
	if ( !CryptoAvailable() ){
		pTarget->SetIdentState(IS_NOTAVAILABLE);
		return false;
	}
	bool bResult;
	try {
		CryptoPP::StringSource ss_Pubkey((byte*)pTarget->GetSecureIdent(),pTarget->GetSecIDKeyLen(),true,0);
		CryptoPP::RSASSA_PKCS1v15_SHA_Verifier pubkey(ss_Pubkey);

		byte abyBuffer[MAXPUBKEYSIZE+9];
		memcpy(abyBuffer,m_abyMyPublicKey,m_nMyPublicKeyLen);
		uint32 challenge = pTarget->m_dwCryptRndChallengeFor;
		wxASSERT ( challenge != 0 );
		PokeUInt32(abyBuffer+m_nMyPublicKeyLen, challenge);


		uint8 nChIpSize = 0;
		if (byChaIPKind != 0){
			nChIpSize = 5;
			uint32 ChallengeIP = 0;
			switch (byChaIPKind) {
				case CRYPT_CIP_LOCALCLIENT:
					ChallengeIP = dwForIP;
					break;
				case CRYPT_CIP_REMOTECLIENT:

					if (!theApp->GetPublicIP(true)) {
						if (::IsLowID(theApp->GetED2KID())){
							AddDebugLogLineN(logCredits, wxT("Warning: Maybe SecureHash Ident fails because LocalIP is unknown"));

							ChallengeIP = theApp->GetPublicIP();
						} else {
							ChallengeIP = theApp->GetED2KID();
						}
					} else {
						ChallengeIP = theApp->GetPublicIP();
					}
					break;
				case CRYPT_CIP_NONECLIENT:
					ChallengeIP = 0;
					break;
			}
			PokeUInt32(abyBuffer+m_nMyPublicKeyLen+4, ChallengeIP);
			PokeUInt8(abyBuffer+m_nMyPublicKeyLen+4+4, byChaIPKind);
		}


 		bResult = pubkey.VerifyMessage(abyBuffer, m_nMyPublicKeyLen+4+nChIpSize, pachSignature, nInputSize);
	} catch (const CryptoPP::Exception& e) {
		AddDebugLogLineC(logCredits, wxString(wxT("Error while verifying identity: ")) + wxString(char2unicode(e.what())));
 		bResult = false;
 	}

	if (!bResult){
		if (pTarget->GetIdentState() == IS_IDNEEDED)
			pTarget->SetIdentState(IS_IDFAILED);
	} else {
		pTarget->Verified(dwForIP);
	}

	return bResult;
}
