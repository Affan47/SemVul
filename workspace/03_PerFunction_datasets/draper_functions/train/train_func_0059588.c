obj_migdata_get_ticket_blob(TSS_HMIGDATA hMigData, UINT32 *migTicketSize, BYTE **migTicket)
{
	struct tsp_object *obj;
	struct tr_migdata_obj *migdata;
	TSS_RESULT result = TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&migdata_list, hMigData)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	migdata = (struct tr_migdata_obj *)obj->data;

	if ((*migTicket = calloc_tspi(obj->tspContext, migdata->migTicketSize)) == NULL) {
		LogError("malloc of %u bytes failed.", migdata->migTicketSize);
		result = TSPERR(TSS_E_OUTOFMEMORY);
		goto done;
	}
	memcpy(*migTicket, migdata->migTicket, migdata->migTicketSize);
	*migTicketSize = migdata->migTicketSize;

done:
	obj_list_put(&migdata_list);

	return result;
}
