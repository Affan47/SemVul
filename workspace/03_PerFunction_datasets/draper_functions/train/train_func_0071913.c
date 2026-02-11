FreeFileTransferMsg(FileTransferMsg ftm)
{

	if(ftm.data != NULL) {
		free(ftm.data);
		ftm.data = NULL;
	}

	ftm.length = 0;

}
