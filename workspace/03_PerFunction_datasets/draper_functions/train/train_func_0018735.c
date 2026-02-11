SendHashsetPacket(const CMD4Hash& forfileid)
{
	CKnownFile* file = theApp->sharedfiles->GetFileByID( forfileid );
	bool from_dq = false;
	if ( !file ) {
		from_dq = true;
		if ((file = theApp->downloadqueue->GetFileByID(forfileid)) == NULL) {
			AddLogLineN(CFormat( _("Hashset requested for unknown file: %s") ) % forfileid.Encode() );

			return;
		}
	}

	if ( !file->GetHashCount() ) {
		if (from_dq) {
			AddDebugLogLineN(logRemoteClient, wxT("Requested hashset could not be found"));
			return;
		} else {
			file = theApp->downloadqueue->GetFileByID(forfileid);
			if (!(file && file->GetHashCount())) {
				AddDebugLogLineN(logRemoteClient, wxT("Requested hashset could not be found"));
				return;
			}
		}
	}

	CMemFile data(1024);
	data.WriteHash(file->GetFileHash());
	uint16 parts = file->GetHashCount();
	data.WriteUInt16(parts);
	for (int i = 0; i != parts; i++) {
		data.WriteHash(file->GetPartHash(i));
	}
	CPacket* packet = new CPacket(data, OP_EDONKEYPROT, OP_HASHSETANSWER);
	theStats::AddUpOverheadFileRequest(packet->GetPacketSize());
	AddDebugLogLineN(logLocalClient, wxT("Local Client: OP_HASHSETANSWER to ") + GetFullIP());
	SendPacket(packet,true,true);
}
