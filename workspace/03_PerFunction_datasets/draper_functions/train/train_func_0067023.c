openMessage(size_t messageNum,
			   string mimeid,
			   bool attachmentsOnly,
			   void (myMessage::*completedFuncArg)())
{
	if (messageNum < size())
		currentMessage=messageNum;


	Curses::keepgoing=false;
	myServer::nextScreen= &folderIndexScreen;
	myServer::nextScreenArg=this;


	if (mymessage == NULL || mymessage->messagesortednum != messageNum
	    || (!attachmentsOnly && !mymessage->isShownMimeId(mimeid)))
	{
		statusBar->clearstatus();
		statusBar->status(_("Reading message..."),
				  statusBar->INPROGRESS);

		CursesMessage *cm=new CursesMessage(getServer()->server,
						    completedFuncArg);

		if (!cm)
			outofmemory();

		try {
			mail::ptr<CursesMessage> cmptr(cm);

			cm->myfolder=this;
			cm->messagesortednum=messageNum;

			messageNum=getServerIndex(messageNum);
			cm->messagenum=messageNum;

			myServer::nextScreen=NULL;

			if (!cm->readAttributes() ||
			    (!attachmentsOnly && !cm->init(mimeid, false)) ||
			    cmptr.isDestroyed())
			{
				if (!cmptr.isDestroyed())
				{
					cm->myfolder=NULL;
					delete cm;
				}

				Curses::keepgoing=false;

				if (myServer::nextScreen == NULL)


				{
					myServer::nextScreen=
						&folderIndexScreen;
					myServer::nextScreenArg=this;
				}
				return;
			}

			mymessage=cm;
		} catch (...) {
			delete cm;
			LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
		}

		if (completedFuncArg)
			cm->beginReformat(80);
	}
	else if (completedFuncArg)
		(mymessage->*completedFuncArg)();

	if (completedFuncArg)
		return;

	Curses::keepgoing=false;
	myServer::nextScreen= &folderIndexScreen;
	myServer::nextScreenArg=this;

	if (mymessage != NULL)
	{
		if (attachmentsOnly)
		{
			statusBar->clearstatus();
			myServer::nextScreen= &showAttachments;
		}
		else
		{
			myServer::nextScreen= &showCurrentMessage;
		}
		myServer::nextScreenArg=mymessage;
	}
}
