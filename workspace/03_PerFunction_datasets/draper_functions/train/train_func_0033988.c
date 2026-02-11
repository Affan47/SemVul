GetAsyncImbpMessage (
		ImbPacket *     msgPtr,
		DWORD 		*msgLen,
		DWORD		timeOut,
		ImbAsyncSeq 	*seqNo,

		DWORD		channelNumber
	)
{

	BOOL                   status;
    BYTE                   responseData[MAX_ASYNC_RESP_SIZE], lun;
	ImbAsyncResponse *     resp = (ImbAsyncResponse *) responseData;
	DWORD                  respLength = sizeof( responseData );
	ImbAsyncRequest        req;

	while(1)
	{


		if( (msgPtr == NULL) || (msgLen == NULL) || ( seqNo == NULL) )
				return ACCESN_ERROR;

				req.timeOut   = timeOut * 1000;
				req.lastSeq   = *seqNo;


			status = DeviceIoControl(       hDevice,
						IOCTL_IMB_GET_ASYNC_MSG,
						& req,
						sizeof( req ),
						& responseData,
						sizeof( responseData ),
						& respLength,
						NULL
					  );

#ifndef NO_MACRO_ARGS
	DEBUG("%s: DeviceIoControl status = %d\n",__FUNCTION__, status);
#endif

			if( status != TRUE ) {
				DWORD error = GetLastError();


				switch( error ) {
					case IMB_MSG_NOT_AVAILABLE:
												return ACCESN_END_OF_DATA;
					default:
											return ACCESN_ERROR;
				}
				return ACCESN_ERROR;
			}
			if( respLength < MIN_ASYNC_RESP_SIZE ) {
					return ACCESN_ERROR;
			}
			respLength -= MIN_ASYNC_RESP_SIZE;

			if( *msgLen < respLength ) {
					return ACCESN_ERROR;
			}


			if ( IpmiVersion == IPMI_09_VERSION)
			{

				switch( channelNumber) {
					case IPMB_CHANNEL:
								lun = IPMB_LUN;
								 break;

					case  EMP_CHANNEL:
								lun = EMP_LUN;
							  	break;

					default:
								lun = RESERVED_LUN;
								break;
				}

				if ( (lun == RESERVED_LUN) ||
					 (lun !=  ((((ImbPacket *)(resp->data))->nfLn) & 0x3 ))
					)
				{
						*seqNo = resp->thisSeq;
						continue;
				}


				memcpy( msgPtr, resp->data, respLength );
				*msgLen = respLength;

			}
			else
			{


				if (resp->data[0] != (BYTE)channelNumber)
				{
					*seqNo = resp->thisSeq;
					continue;
				}

				memcpy( msgPtr, &(resp->data[1]), respLength-1 );
				*msgLen = respLength-1;


			}


		*seqNo = resp->thisSeq;

		return ACCESN_OK;

	}
}
