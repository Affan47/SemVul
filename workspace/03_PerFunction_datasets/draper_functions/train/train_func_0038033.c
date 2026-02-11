isns_create_scn_registration2(isns_client_t *clnt, unsigned int bitmap, isns_source_t *source)
{
	isns_simple_t	*call;

	if (!source)
		source = clnt->ic_source;
	call = isns_simple_create(ISNS_SCN_REGISTER, source, NULL);
	if (call) {
		isns_attr_list_append_attr(&call->is_message_attrs,
				isns_source_attr(source));
		isns_attr_list_append_uint32(&call->is_operating_attrs,
				ISNS_TAG_ISCSI_SCN_BITMAP,
				bitmap);
	}
	return call;
}
