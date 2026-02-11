FCEU_UpdateInput(void)
{

	if(!FCEUMOV_Mode(MOVIEMODE_PLAY))
	{
		for(int port=0;port<2;port++)
			joyports[port].driver->Update(port,joyports[port].ptr,joyports[port].attrib);
		portFC.driver->Update(portFC.ptr,portFC.attrib);
	}

	if(GameInfo->type==GIT_VSUNI)
		if(coinon) coinon--;

	if(FCEUnetplay)
		NetplayUpdate(joy);

	FCEUMOV_AddInputState();


	if(GameInfo->type==GIT_VSUNI)
		FCEU_VSUniSwap(&joy[0],&joy[1]);
}
