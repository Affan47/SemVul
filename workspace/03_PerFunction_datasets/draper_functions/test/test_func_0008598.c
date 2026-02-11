StartAsyncMesgPoll()
{

	DWORD   retLength;
	BOOL    status;

#ifndef NO_MACRO_ARGS
	DEBUG("%s: DeviceIoControl cmd = %x\n",__FUNCTION__,IOCTL_IMB_POLL_ASYNC);
#endif
	status = DeviceIoControl (      hDevice,
								IOCTL_IMB_POLL_ASYNC,
								NULL,
								0,
								NULL,
								0,
								& retLength,
								0
							);

#ifndef NO_MACRO_ARGS
	DEBUG("%s: DeviceIoControl status = %d\n",__FUNCTION__, status);
#endif

	if( status == TRUE ) {
		return ACCESN_OK;
	} else {
		return ACCESN_ERROR;
	}

}
