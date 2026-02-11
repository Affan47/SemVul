ExportFile(FCDocument* fcdocument, const fchar* filePath)
{
	bool status = true;

	fcdocument->SetFileUrl(fstring(filePath));

	_FTRY
	{

		FUXmlDocument daeDocument(NULL, filePath, false);
		xmlNode* rootNode = daeDocument.CreateRootNode(DAE_COLLADA_ELEMENT);
		status = ExportDocument(fcdocument, rootNode);
		if (status)
		{

			if (!daeDocument.Write())
			{
				FUError::Error(FUError::ERROR_LEVEL, FUError::ERROR_WRITE_FILE, rootNode->line);
			}
			else
			{
				FUError::Error(FUError::DEBUG_LEVEL, FUError::DEBUG_WRITE_SUCCESSFUL);
			}
		}
	}
    _FCATCH_ALL
	{
		FUError::Error(FUError::ERROR_LEVEL, FUError::ERROR_PARSING_FAILED);
	}

	return status;
}
