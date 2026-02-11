Add(const String &signature, ResultList *entry)
{
	ResultList *previous = (ResultList *)cache[signature];
	if(previous && previous != empty)
	{
		delete previous;
	}
	if(!entry)
	{
		entry = empty;
	}
	cache.Add(signature, entry);
}
