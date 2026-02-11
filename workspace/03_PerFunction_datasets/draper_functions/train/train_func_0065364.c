DeactivateCheat(CheatEntry * entry)
{
	int	i;

	for(i = 0; i < entry->actionListLength; i++)
	{
		CheatAction	* action = &entry->actionList[i];

		if(	EXTRACT_FIELD(action->type, RestorePreviousValue) &&
			(action->flags & kActionFlag_LastValueGood))
		{
			WriteData(action, action->lastValue);

			action->flags &= ~kActionFlag_LastValueGood;
		}
	}

	RemoveAssociatedWatches(entry);

	entry->flags &= ~kCheatFlag_StateMask;
}
