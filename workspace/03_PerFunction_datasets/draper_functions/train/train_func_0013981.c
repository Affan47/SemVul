atp_tool_list_deactivate (ATPToolList *this)
{
	ATPUserTool *next;

	for (next = atp_tool_list_first (this); next != NULL; next = atp_user_tool_next (next))
	{
		atp_user_tool_deactivate (next, next->owner->ui);
	}

	return TRUE;
}
