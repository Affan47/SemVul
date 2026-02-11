Near(const ResultList &l, const ResultList &r)
{
	ResultList *result = 0;
	DictionaryCursor c;
	l.Start_Get(c);
	DocMatch *match = (DocMatch *)l.Get_NextElement(c);
	while(match)
	{
		DocMatch *confirm = r.find(match->GetId());
		if(confirm)
		{
			List *locations = MergeLocations(
						*match->GetLocations(),
						*confirm->GetLocations());
			if(locations)
			{
				if(!result)
				{
					result = new ResultList;
				}
				DocMatch *copy = new DocMatch(*match);
				copy->SetLocations(locations);
				result->add(copy);
			}
		}
		match = (DocMatch *)l.Get_NextElement(c);
	}
	return result;
}
