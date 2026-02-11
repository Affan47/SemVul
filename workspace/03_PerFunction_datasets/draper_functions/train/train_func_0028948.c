AT_WritePhonebook(gn_data *data, struct gn_statemachine *state)
{
	at_driver_instance *drvinst = AT_DRVINST(state);
	int len, ofs;
	char req[256], *tmp;
	char number[64];
	gn_error ret;

	ret = at_memory_type_set(data->phonebook_entry->memory_type, state);
	if (ret)
		return ret;
	if (data->phonebook_entry->empty) {
		return AT_DeletePhonebook(data, state);
	} else {
		ret = state->driver.functions(GN_OP_AT_SetCharset, data, state);
		if (ret)
			return ret;
		memset(number, 0, sizeof(number));
		if (drvinst->encode_number)
			at_encode(drvinst->charset, number, sizeof(number),
				data->phonebook_entry->number,
				strlen(data->phonebook_entry->number));
		else
			strncpy(number, data->phonebook_entry->number, sizeof(number));
		ofs = snprintf(req, sizeof(req), "AT+CPBW=%d,\"%s\",%s,\"",
			       data->phonebook_entry->location+drvinst->memoryoffset,
			       number,
			       data->phonebook_entry->number[0] == '+' ? "145" : "129");
		tmp = req + ofs;
		len = at_encode(drvinst->charset, tmp, sizeof(req) - ofs,
				data->phonebook_entry->name,
				strlen(data->phonebook_entry->name));
		tmp[len-1] = '"';
		tmp[len++] = '\r';
		len += ofs;
	}
	if (sm_message_send(len, GN_OP_WritePhonebook, req, state))
		return GN_ERR_NOTREADY;
	return sm_block_no_retry(GN_OP_WritePhonebook, data, state);
}
