moveToWaste(LexizeData *ld, ParsedLex *stop)
{
	bool		go = true;

	while (ld->towork.head && go)
	{
		if (ld->towork.head == stop)
		{
			ld->curSub = stop->next;
			go = false;
		}
		RemoveHead(ld);
	}
}
