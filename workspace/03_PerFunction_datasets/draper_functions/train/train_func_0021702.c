go()
{
	ostringstream msgList;

	doFetchingStructure=NULL;
	fetchingMessageNum=0;
	fetchingStructCount=0;
	seenMimeVersion=false;

	if (!myimap->currentFolder ||
	    myimap->currentFolder->closeInProgress ||
	    !(fetchList >> msgList))
	{
		return false;
	}

	bool hasAttr=false;

	if (attributes & mail::account::ARRIVALDATE)
	{
		msgList << " INTERNALDATE";
		hasAttr=true;
	}

	if (attributes & mail::account::MESSAGESIZE)
	{
		msgList << " SIZE";
		hasAttr=true;
	}

	if (attributes & mail::account::MIMESTRUCTURE)
	{
		msgList << " CONTENTS.PEEK=MIME(:MIME)";
		hasAttr=true;
		fetchingStructure=mail::mimestruct();
		fetchingStructure.type="TEXT";
		fetchingStructure.subtype="PLAIN";
	}
	else

		if (attributes & mail::account::ENVELOPE)
	{
		msgList << " CONTENTS.PEEK=HEADERS(:ENVELOPE)";
		hasAttr=true;
	}

	if (!hasAttr)
		return false;

	doFetchingEnvelope=false;
	myimap->imapcmd("", "FETCH" + msgList.str() + "\n");
	return true;
}
