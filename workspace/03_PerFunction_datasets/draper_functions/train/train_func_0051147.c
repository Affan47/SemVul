spi_populate_tag_msg(unsigned char *msg, struct scsi_cmnd *cmd)
{
        if (cmd->flags & SCMD_TAGGED) {
		*msg++ = SIMPLE_QUEUE_TAG;
        	*msg++ = cmd->request->tag;
        	return 2;
	}

	return 0;
}
