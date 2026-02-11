sf_outbound_ds(unsigned char buf[], int buflen)
{
	enum pds rv;

	if (buflen < 5) {
		trace_ds(" error: field length %d too short\n", buflen);
		return PDS_BAD_CMD;
	}

	trace_ds("(0x%02x)", buf[3]);
	if (buf[3] != 0x00) {
		trace_ds(" error: illegal partition 0x%0x\n", buf[3]);
		return PDS_BAD_CMD;
	}

	switch (buf[4]) {
	    case SNA_CMD_W:
		trace_ds(" Write");
		if (buflen > 5) {
			if ((rv = ctlr_write(&buf[4], buflen-4, False)) < 0)
				return rv;
		} else
			trace_ds("\n");
		break;
	    case SNA_CMD_EW:
		trace_ds(" EraseWrite");
		ctlr_erase(screen_alt);
		if (buflen > 5) {
			if ((rv = ctlr_write(&buf[4], buflen-4, True)) < 0)
				return rv;
		} else
			trace_ds("\n");
		break;
	    case SNA_CMD_EWA:
		trace_ds(" EraseWriteAlternate");
		ctlr_erase(screen_alt);
		if (buflen > 5) {
			if ((rv = ctlr_write(&buf[4], buflen-4, True)) < 0)
				return rv;
		} else
			trace_ds("\n");
		break;
	    case SNA_CMD_EAU:
		trace_ds(" EraseAllUnprotected\n");
		ctlr_erase_all_unprotected();
		break;
	    default:
		trace_ds(" unknown type 0x%02x\n", buf[4]);
		return PDS_BAD_CMD;
	}
	return PDS_OKAY_NO_OUTPUT;
}
