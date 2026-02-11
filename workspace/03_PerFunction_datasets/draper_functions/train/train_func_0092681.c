item_get_dcc(WI_ITEM_REC *item)
{
	QUERY_REC *query;

	query = IRC_QUERY(item);
	if (query == NULL || *query->name != '=')
		return NULL;

	return dcc_chat_find_id(query->name+1);
}
