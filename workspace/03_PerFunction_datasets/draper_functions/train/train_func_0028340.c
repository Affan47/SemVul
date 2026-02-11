tliInHistory(TimeLineID tli, List *expectedTLEs)
{
	ListCell   *cell;

	foreach(cell, expectedTLEs)
	{
		if (((TimeLineHistoryEntry *) lfirst(cell))->tli == tli)
			return true;
	}

	return false;
}
