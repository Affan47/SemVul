messagesRemoved(vector< pair<size_t, size_t> >
				     &removedList)
{


	vector< pair<size_t, size_t> >::iterator
		b=removedList.begin(),
		e=removedList.end();

	while (b != e)
	{
		--e;

		size_t i=e->first;
		size_t j=e->second+1;

		if (exists >= j)
			exists -= j - i;
		else if (exists > i)
			exists=i;

		if (restoringSnapshot)
		{
			if (presnapshotExists >= j)
				presnapshotExists -= j - i;
			else if (presnapshotExists > i)
				presnapshotExists=i;
		}
	}
}
