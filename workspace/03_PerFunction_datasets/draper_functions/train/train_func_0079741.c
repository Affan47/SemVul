Ban(){
	theApp->clientlist->AddTrackClient(this);
	theApp->clientlist->AddBannedClient( GetIP() );

	AddDebugLogLineN(logClient, wxT("Client '") + GetUserName() + wxT("' seems to be an aggressive client and is banned from the uploadqueue"));

	SetUploadState(US_BANNED);

	Notify_SharedCtrlRefreshClient(ECID(), UNAVAILABLE_SOURCE);
}
