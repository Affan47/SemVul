setActiveColumn(s32 idx, bool doOrder )
{
	if (idx < 0 || idx >= (s32)Columns.size())
		return false;

	bool changed = (ActiveTab != idx);

	ActiveTab = idx;
	if ( ActiveTab < 0 )
		return false;

	if ( doOrder )
	{
		switch ( Columns[idx].OrderingMode )
		{
			case EGCO_NONE:
				CurrentOrdering = EGOM_NONE;
				break;

			case EGCO_CUSTOM:
				CurrentOrdering = EGOM_NONE;
				if (Parent)
				{
					SEvent event;
					event.EventType = EET_GUI_EVENT;
					event.GUIEvent.Caller = this;
					event.GUIEvent.Element = 0;
					event.GUIEvent.EventType = EGET_TABLE_HEADER_CHANGED;
					Parent->OnEvent(event);
				}

				break;

			case EGCO_ASCENDING:
				CurrentOrdering = EGOM_ASCENDING;
				break;

			case EGCO_DESCENDING:
				CurrentOrdering = EGOM_DESCENDING;
				break;

			case EGCO_FLIP_ASCENDING_DESCENDING:
				CurrentOrdering = EGOM_ASCENDING == CurrentOrdering ? EGOM_DESCENDING : EGOM_ASCENDING;
				break;
			default:
				CurrentOrdering = EGOM_NONE;
		}

		orderRows(getActiveColumn(), CurrentOrdering);
	}

	if (changed)
	{
		SEvent event;
		event.EventType = EET_GUI_EVENT;
		event.GUIEvent.Caller = this;
		event.GUIEvent.Element = 0;
		event.GUIEvent.EventType = EGET_TABLE_HEADER_CHANGED;
		Parent->OnEvent(event);
	}

	return true;
}
