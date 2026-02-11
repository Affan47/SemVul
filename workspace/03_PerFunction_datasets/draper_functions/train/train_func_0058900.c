WriteCD(int cd_desc, char CmdData, char *Buffer, unsigned int timeout,
		uint32_t DataLen)
{
	int ret;

	ret = AMI_SPT_CMD_SendCmd(cd_desc, Buffer, CmdData, DataLen, timeout);
	if ( ret != 0 ) {
		lprintf(LOG_ERR, "Error while writing to CD-Drive");
		return -1;
	}

	return 0;
}
