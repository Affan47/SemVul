avc1394_unit_info(raw1394handle_t handle, nodeid_t node)
{

	quadlet_t  request[2];
	quadlet_t *response;

	request[0] = AVC1394_CTYPE_STATUS | AVC1394_SUBUNIT_TYPE_UNIT
	             | AVC1394_SUBUNIT_ID_IGNORE | AVC1394_COMMAND_UNIT_INFO | 0xFF;
	request[1] = 0xFFFFFFFF;
	response = avc1394_transaction_block(handle, node, request, 2, AVC1394_RETRY);
	if (response == NULL)
		return NULL;

#ifdef DEBUG
	fprintf(stderr, "avc_unit_info: 0x%08X 0x%08X\n",
			response[0], response[1]);
#endif
	return response;
}
