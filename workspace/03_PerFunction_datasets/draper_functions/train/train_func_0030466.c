target_fcp_handler( raw1394handle_t handle, nodeid_t nodeid, int response,
	size_t length, unsigned char *data )
{
	int result;
	struct avc1394_command_response cmd_resp;
	quadlet_t *r = (quadlet_t *) &cmd_resp;


	memset(&cmd_resp, 0, sizeof(cmd_resp));
	memcpy(r, data, length);

	if ( response != 0 )
	{
		return 0;
	}
	else
	{
#ifdef DEBUG
		{
		int q, z;
		z = (length % 4) ? length + (4 - (length % 4)) : length;
		printf("----> ");
		for (q = 0; q < z / 4; q++)
		    printf("%08x ", r[q]);
		printf("(length %d)\n", length);
		printf("----> type=0x%02x subunit_type=0x%x subunit_id=0x%x opcode=0x%x operand0=0x%x\n",
			cmd_resp.status, cmd_resp.subunit_type,
			cmd_resp.subunit_id, cmd_resp.opcode, cmd_resp.operand[0]);
	    }
#endif
		result = g_command_handler( &cmd_resp );

		if (result == 0)
			cmd_resp.status = AVC1394_RESP_NOT_IMPLEMENTED;

#ifdef DEBUG
		{
		int q, z;
		z = (length % 4) ? length + (4 - (length % 4)) : length;
		printf("<---- ");
		for (q = 0; q < z / 4; q++)
		    printf("%08x ", r[q]);
		printf("(length %d)\n", length);
		printf("<---- type=0x%02x subunit_type=0x%x subunit_id=0x%x opcode=0x%x operand0=0x%x\n",
			cmd_resp.status, cmd_resp.subunit_type,
			cmd_resp.subunit_id, cmd_resp.opcode, cmd_resp.operand[0]);
	    }
#endif

		return cooked1394_write(handle, 0xffc0 | nodeid, FCP_RESPONSE_ADDR, length, r);
	}
}
