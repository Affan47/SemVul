MergeLocations(const List &p, const List &q)
{
	List *result = 0;
	ListCursor pc;
	p.Start_Get(pc);
	const Location *left = (const Location *)p.Get_Next(pc);
	while(left)
	{
		ListCursor qc;
		q.Start_Get(qc);
		const Location *right = (const Location *)q.Get_Next(qc);
		while(right)
		{
			if(left->to + 1 == right->from)
			{
				double prevsize = left->to - left->from + 1.0;
				double addsize = right->to - right->from + 1.0;
				double weight =
					((left->weight * prevsize) +
					(right->weight * addsize)) /
					(right->to - left->from + 1.0);

				if(!result)
				{
					result = new List;
				}

				result->Add(new Location(
						left->from,
						right->to,
						left->flags & right->flags,
						weight));
				break;
			}
			right = (const Location *)q.Get_Next(qc);
		}
		left = (const Location *)p.Get_Next(pc);
	}
	return result;
}
