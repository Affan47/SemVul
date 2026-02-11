atp_user_tool_override (const ATPUserTool *this)
{
	ATPUserTool* tool;

	for (tool = g_hash_table_lookup (this->owner->hash, this->name);
		 tool != NULL; tool = tool->over)
	{
		if (tool->over == this) return tool;
	}

	return NULL;
}
