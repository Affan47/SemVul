ProcessAICHFileHash(CMemFile* data, const CPartFile* file){
	CPartFile* pPartFile;
	if (file == NULL){
		pPartFile = theApp->downloadqueue->GetFileByID(data->ReadHash());
	} else {
		pPartFile = (CPartFile*)file;
	}
	CAICHHash ahMasterHash(data);

	if(pPartFile != NULL && pPartFile == GetRequestFile()){
		SetReqFileAICHHash(new CAICHHash(ahMasterHash));
		pPartFile->GetAICHHashset()->UntrustedHashReceived(ahMasterHash, GetConnectIP());
	} else {
		AddDebugLogLineN( logAICHTransfer, wxT("ProcessAICHFileHash(): PartFile not found or Partfile differs from requested file, ") + GetClientFullInfo() );
	}
}
