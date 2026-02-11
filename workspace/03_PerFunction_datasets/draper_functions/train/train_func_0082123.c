msg_out_fd(void *data, const void *mesg, size_t mesglen)
{
	if (data && mesg)
		if (write(*(MsgFDData *)data, mesg, mesglen) == -1)
			;
}
