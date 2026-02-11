DtsCheckKeyFrame(HANDLE hDevice, uint8_t *pBuffer)
{
	DTS_LIB_CONTEXT *Ctx = NULL;
	DTS_GET_CTX(hDevice,Ctx);


	bool bKeyFrame = false;
	int iType = 0;


	if((Ctx->VidParams.MediaSubType == BC_MSUBTYPE_WVC1) || (Ctx->VidParams.MediaSubType == BC_MSUBTYPE_WMVA))
	{


		if(!Ctx->VidParams.Progressive)
		{


			if((pBuffer[0] & 0x20) == 0)
			{
				iType = 0;
			}

			else if((pBuffer[0] & 0x10) == 0)
			{
				iType = 1;
			}

			else if((pBuffer[0] & 0x08) == 0)
			{
				iType = 2;
			}

			else if((pBuffer[0] & 0x04) == 0)
			{
				iType = 3;
			}
		}
		else
		{


			if((pBuffer[0] & 0x80) == 0)
			{
				iType = 0;
			}

			else if((pBuffer[0] & 0x40) == 0)
			{
				iType = 1;
			}

			else if((pBuffer[0] & 0x20) == 0)
			{
				iType = 2;
			}

			else if((pBuffer[0] & 0x10) == 0)
			{
				iType = 3;
			}
		}


		if(iType == 2)
		{
			bKeyFrame = true;
		}
	}
	else
	{


		int iCurrentBit = 0;

		if(Ctx->PESConvParams.m_bFinterpFlag)
		{
			iCurrentBit = iCurrentBit + 1;
		}


		iCurrentBit = iCurrentBit + 2;


		if(Ctx->PESConvParams.m_bRangered)
		{
			iCurrentBit = iCurrentBit + 1;
		}


		uint8_t bFirstCheck = 0;
		uint8_t bSecondCheck = 0;
		if(iCurrentBit == 2)
		{
			bFirstCheck = 0x20;
			bSecondCheck = 0x10;
		}
		else if(iCurrentBit == 3)
		{
			bFirstCheck = 0x10;
			bSecondCheck = 0x08;
		}
		else if(iCurrentBit == 4)
		{
			bFirstCheck = 0x08;
			bSecondCheck = 0x04;
		}

		if(pBuffer[0] & bFirstCheck)
		{
			iType = 0;
		}
		else if(!Ctx->PESConvParams.m_bMaxbFrames)
		{
			iType = 2;
		}
		else if(pBuffer[0] & bSecondCheck)
		{
			iType = 2;
		}
		else
		{
			iType = 1;
		}


		if(iType == 2)
		{
			bKeyFrame = true;
		}
	}

	if (bKeyFrame)
	{
		Ctx->PESConvParams.m_bAddSpsPps = true;
	}
	return BC_STS_SUCCESS;
}
