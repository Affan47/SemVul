loggedIn()
{
	mail::callback *myCallback=callbackPtr;

	callbackPtr=NULL;

	mail::ptr<mail::pop3> serverPtr= myserver;

	bool changedFolder=myserver->reconcileFolderIndex();

	if (forceSaveSnapshot)
		changedFolder=true;


	if (!serverPtr.isDestroyed() && serverPtr->folderCallback &&
	    changedFolder)
		serverPtr->folderCallback->saveSnapshot("POP3");

	if (!serverPtr.isDestroyed())
	{
		if (serverPtr->ispop3maildrop())
		{
			serverPtr->pop3maildropreset();

			callbackPtr=myCallback;

			next2Download=1;
			messagesEstimatedTotal=myserver->listMap.size();
			doNextDownload();
			return;
		}
		done();
	}

	if (myCallback)
		myCallback->success("OK");
}
