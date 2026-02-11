DownloadFromSubdirectory(FileList &localFiles, const char *subdir, const char *outputSubdir, bool prependAppDirToOutputSubdir, SystemAddress host, FileListTransferCBInterface *onFileCallback, PacketPriority _priority, char _orderingChannel, FileListProgress *cb)
{
	RakAssert(host!=UNASSIGNED_SYSTEM_ADDRESS);

	DDTCallback *transferCallback;

	localFiles.AddCallback(cb);


	transferCallback = RakNet::OP_NEW<DDTCallback>( _FILE_AND_LINE_ );
	if (subdir && subdir[0])
	{
		transferCallback->subdirLen=(unsigned int)strlen(subdir);
		if (subdir[transferCallback->subdirLen-1]!='/' && subdir[transferCallback->subdirLen-1]!='\\')
			transferCallback->subdirLen++;
	}
	else
		transferCallback->subdirLen=0;
	if (prependAppDirToOutputSubdir)
		strcpy(transferCallback->outputSubdir, applicationDirectory);
	else
		transferCallback->outputSubdir[0]=0;
	if (outputSubdir)
		strcat(transferCallback->outputSubdir, outputSubdir);
	if (transferCallback->outputSubdir[strlen(transferCallback->outputSubdir)-1]!='/' && transferCallback->outputSubdir[strlen(transferCallback->outputSubdir)-1]!='\\')
		strcat(transferCallback->outputSubdir, "/");
	transferCallback->onFileCallback=onFileCallback;


	unsigned short setId = fileListTransfer->SetupReceive(transferCallback, true, host);


	RakNet::BitStream outBitstream;
	outBitstream.Write((MessageID)ID_DDT_DOWNLOAD_REQUEST);
	outBitstream.Write(setId);
	StringCompressor::Instance()->EncodeString(subdir, 256, &outBitstream);
	StringCompressor::Instance()->EncodeString(outputSubdir, 256, &outBitstream);
	localFiles.Serialize(&outBitstream);
	SendUnified(&outBitstream, _priority, RELIABLE_ORDERED, _orderingChannel, host, false);

	return setId;
}
