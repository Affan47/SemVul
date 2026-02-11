reconcileFolderIndex()
{
	set<size_t> messagesSeen;

	map<string, int>::iterator ub, ue;

	size_t i;

	bool needSnapshot=false;


	mail::expungeList removedList;

	for (i=currentFolderIndex.size(); i; )
	{
		string uid=currentFolderIndex[--i].uid;

		if (uidlMap.count( uid ) == 0)
		{
			removedList << i;
			needSnapshot=true;
		}
		else
			messagesSeen.insert(uidlMap.find(uid)->second);
	}


	MONITOR(mail::pop3);

	mail::expungeList::iterator expungeIterator;

	for (expungeIterator=removedList.end();
	     expungeIterator != removedList.begin(); )
	{
		--expungeIterator;
		currentFolderIndex.erase(currentFolderIndex.begin() +
					 expungeIterator->first,
					 currentFolderIndex.begin() +
					 expungeIterator->second+1);
	}

	if (folderCallback)
		removedList >> folderCallback;


	if (!DESTROYED())
	{
		vector<string> newUids;

		ub=uidlMap.begin();
		ue=uidlMap.end();


		while (ub != ue)
		{
			if (messagesSeen.count(ub->second) == 0)
				newUids.push_back(ub->first);
			ub++;
		}
		sort(newUids.begin(), newUids.end(),
		     CheckNewMailTask::sortNewMail(uidlMap));

		vector<string>::iterator b, e;

		b=newUids.begin(), e=newUids.end();

		while (b != e)
		{
			pop3MessageInfo newInfo;


			newInfo.unread=true;
			newInfo.uid= *b++;
			currentFolderIndex.push_back(newInfo);
		}

		if (newUids.size() > 0 && folderCallback)

		{
			needSnapshot=true;
			folderCallback->newMessages();
		}
	}
	return needSnapshot;
}
