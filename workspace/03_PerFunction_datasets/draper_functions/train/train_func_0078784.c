MoveBookmarkHub( int oldpos, int newpos )
{
	if ( oldpos == newpos )
	{
		return true;
	}

	if ( ((oldpos - newpos) != 1) && ((newpos - oldpos) != 1) )
	{
		printf("MoveBookmarkHub: can only move adjacent bookmarks\n");
		return false;
	}

	bool suceeded = false;

	m_Mutex.Lock();

	OrderedBookmarkMap::const_iterator it1 = pOrderedBookmarks->find( oldpos );

	if ( it1 != pOrderedBookmarks->end() )
	{
		OrderedBookmarkMap::const_iterator it2= pOrderedBookmarks->find( newpos );
		if ( it2 != pOrderedBookmarks->end() )
		{
			DCConfigHubItem * item1 = it1->second;
			DCConfigHubItem * item2 = it2->second;

			pOrderedBookmarks->erase( oldpos );
			pOrderedBookmarks->erase( newpos );

			item1->m_nPosition = newpos;
			item2->m_nPosition = oldpos;

			(*pOrderedBookmarks)[newpos] = item1;
			(*pOrderedBookmarks)[oldpos] = item2;

			suceeded = true;
		}
		else
		{
			printf("MoveBookmarkHub: new position not valid\n");
		}

	}
	else
	{
		printf("MoveBookmarkHub: old position not valid\n");
	}

	m_Mutex.UnLock();

	return suceeded;
}
