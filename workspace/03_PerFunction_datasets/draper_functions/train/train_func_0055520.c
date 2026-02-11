isns_source_decode(buf_t *bp, isns_source_t **result)
{
	isns_attr_t	*attr;
	int		status;

	status = isns_attr_decode(bp, &attr);
	if (status == ISNS_SUCCESS) {


		switch (attr->ia_tag_id) {
#if 0
		case ISNS_TAG_DELIMITER:
			*result = NULL;
			break;
#endif

		case ISNS_TAG_ISCSI_NAME:
			*result = __isns_source_create(attr);
			break;

		case ISNS_TAG_FC_PORT_NAME_WWPN:
			*result = __isns_source_create(attr);
			break;

		default:
			isns_attr_release(attr);
			return ISNS_SOURCE_UNKNOWN;
		}
	}
	return status;
}
