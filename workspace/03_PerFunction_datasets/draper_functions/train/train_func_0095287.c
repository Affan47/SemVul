scan_snmp_get_manufacturer(char* oid_str,void* handle)
{
        size_t name_len;
        oid name[MAX_OID_LEN];
	struct snmp_pdu *pdu, *response = NULL;
	int status;
	int index = 0;


	name_len = MAX_OID_LEN;
	if (!(*nut_snmp_parse_oid)(oid_str, name, &name_len)) {
		index++;
		return NULL;
	}

	pdu = (*nut_snmp_pdu_create)(SNMP_MSG_GET);

	if (pdu == NULL) {
		index++;
		return NULL;
	}

	(*nut_snmp_add_null_var)(pdu, name, name_len);

	status = (*nut_snmp_sess_synch_response)(handle,pdu, &response);
	if( response == NULL ) {
		index++;
		return NULL;
	}

	if(status!=STAT_SUCCESS||response->errstat!=SNMP_ERR_NOERROR||
			response->variables == NULL ||
			response->variables->name == NULL ||
			(*nut_snmp_oid_compare)(response->variables->name,
				response->variables->name_length,
				name, name_len) != 0 ||
			response->variables->val.string == NULL ) {
		(*nut_snmp_free_pdu)(response);
		index++;
		return NULL;
	}

	return response;
}
