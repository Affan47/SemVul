avc1394_vcr_is_recording(raw1394handle_t handle, nodeid_t node)
{
	quadlet_t response = avc1394_transaction(handle, node, STATVCR0
		| AVC1394_VCR_COMMAND_TRANSPORT_STATE | AVC1394_VCR_OPERAND_TRANSPORT_STATE,
		AVC1394_RETRY);
	if (AVC1394_MASK_OPCODE(response)
		== AVC1394_VCR_RESPONSE_TRANSPORT_STATE_RECORD)
		return AVC1394_GET_OPERAND0(response);
	else
		return 0;
}
