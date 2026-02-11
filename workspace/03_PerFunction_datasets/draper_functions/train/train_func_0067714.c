serverResponse(const char *message)
{
	if (*message != '+')
	{
		loginFailed(message);
		return;
	}


	while (updateIndex < myserver->currentFolderIndex.size())
	{
		string uid;

		if (myserver->currentFolderIndex[updateIndex].deleted &&
		    myserver->uidlMap.count(uid=myserver->currentFolderIndex
					   [updateIndex].uid) > 0)
		{
			int msgNum=myserver->uidlMap.find(uid)->second;

			string buffer;
			{
				ostringstream o;

				o << msgNum;
				buffer=o.str();
			}

			++updateIndex;
			myserver->socketWrite(string("DELE ") + buffer
					     + "\r\n");
			return;
		}
		++updateIndex;
	}


	ForceCheckNewMailTask *l=
		new ForceCheckNewMailTask(callbackPtr, myserver);

	if (!l)
	{
		loginFailed("Out of memory.");
		return;
	}

	callbackPtr=NULL;

	if ( (*myserver->tasks.begin()) != this)
		kill(getpid(), SIGABRT);

	try {
		LogoutTask *lo=new LogoutTask( *myserver, l, true);

		if (!lo)
			strerror(errno);

		try {
			myserver->tasks.insert(++myserver->tasks.begin(),
					      lo);
		} catch (...) {
			delete lo;
			LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
		}
	} catch (...) {
		delete l;
		LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
	}
	done();
}
