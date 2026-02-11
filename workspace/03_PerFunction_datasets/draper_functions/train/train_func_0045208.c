PauseFile(bool bInsufficient)
{
	SetActive(false);

	if ( status == PS_COMPLETE || status == PS_COMPLETING ) {
		return;
	}

	if (GetKadFileSearchID()) {
		Kademlia::CSearchManager::StopSearch(GetKadFileSearchID(), true);

		m_LastSearchTimeKad = 0;
	}

	m_iLastPausePurge = time(NULL);

	theApp->downloadqueue->RemoveLocalServerRequest(this);

	CPacket packet( OP_CANCELTRANSFER, 0, OP_EDONKEYPROT );
	for( SourceSet::iterator it = m_SrcList.begin(); it != m_SrcList.end(); ) {
		CUpDownClient* cur_src = it++->GetClient();
		if (cur_src->GetDownloadState() == DS_DOWNLOADING) {
			if (!cur_src->GetSentCancelTransfer()) {
				theStats::AddUpOverheadOther( packet.GetPacketSize() );
				AddDebugLogLineN( logLocalClient, wxT("Local Client: OP_CANCELTRANSFER to ") + cur_src->GetFullIP() );
				cur_src->SendPacket( &packet, false, true );
				cur_src->SetSentCancelTransfer( true );
			}
			cur_src->SetDownloadState(DS_ONQUEUE);

			cur_src->ResetLastAskedTime();
		}
	}


	m_insufficient = bInsufficient;
	m_paused = true;


	kBpsDown = 0.0;
	transferingsrc = 0;

	SetStatus(status);
}
