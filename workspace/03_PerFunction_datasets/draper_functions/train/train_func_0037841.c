DtsReceiveFWDiagRes(HANDLE hDevice, PBC_FWDIAG_RES_BLOCK_ST pBlMsg,uint32_t wait)
{
	BC_STATUS status = BC_STS_ERROR;
	uint32_t chkSum = 0;
	uint32_t cnt=1000;

	while(--cnt) {
		status = DtsDevMemRd(hDevice,(uint32_t *)(pBlMsg),sizeof(BC_FWDIAG_RES_BLOCK_ST),BC_FWDIAG_RES_ADDR);
		if(BC_STS_SUCCESS != status){

			DebugLog_Trace(LDIL_DBG,"Command Failure From DIL status:%x\n",status);
			return (status);
		}

		if(pBlMsg->done&BC_FWDIAG_RES_POSTED) {
			chkSum = ~(pBlMsg->done+pBlMsg->status+pBlMsg->detail[0]+\
				pBlMsg->detail[1]+pBlMsg->detail[2]+pBlMsg->detail[3]+pBlMsg->detail[4]);

			if(chkSum != pBlMsg->chk_sum)
			{
				DebugLog_Trace(LDIL_DBG,"Recv. Message Checksum failed\n");
				return BC_STS_ERROR;
			}


			break;
		}

		bc_sleep_ms(wait);
	}


	DtsClearFWDiagCommBlock(hDevice);

	if(!cnt){
		DebugLog_Trace(LDIL_DBG,"Message Receive Timed-out\n");
		return BC_STS_TIMEOUT;
	}

	return BC_STS_SUCCESS;
}
