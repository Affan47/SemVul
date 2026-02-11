RPC_ForceClear(TSS_HCONTEXT tspContext)
{
	TSS_RESULT result = (TSS_E_INTERNAL_ERROR | TSS_LAYER_TSP);
	struct host_table_entry *entry = get_table_entry(tspContext);

	if (entry == NULL)
		return TSPERR(TSS_E_NO_CONNECTION);

	switch (entry->type) {
		case CONNECTION_TYPE_TCP_PERSISTANT:
			result = RPC_ForceClear_TP(entry);
			break;
		default:
			break;
	}

	put_table_entry(entry);

	return result;
}
