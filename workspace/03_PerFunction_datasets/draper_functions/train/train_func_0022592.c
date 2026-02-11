__isns_simple_encode(isns_simple_t *simp, buf_t *bp)
{
	int	status = ISNS_SUCCESS;

	if (isns_simple_include_source(simp->is_function)) {
		if (simp->is_source == NULL) {
			isns_error("Cannot encode %s message - caller forgot to set source\n",
				  isns_function_name(simp->is_function));
			return ISNS_SOURCE_UNKNOWN;
		}
		status = isns_source_encode(bp, simp->is_source);
	}

	if (status == ISNS_SUCCESS)
		status = isns_attr_list_encode(bp, &simp->is_message_attrs);


	switch (simp->is_function & 0x7fff) {


	case ISNS_SCN_DEREGISTER:
	case ISNS_ENTITY_STATUS_INQUIRY:
	case ISNS_STATE_CHANGE_NOTIFICATION:
		break;

	default:
		if (status == ISNS_SUCCESS)
			status = isns_encode_delimiter(bp);
		if (status == ISNS_SUCCESS)
			status = isns_attr_list_encode(bp, &simp->is_operating_attrs);
		break;
	}

	return status;
}
