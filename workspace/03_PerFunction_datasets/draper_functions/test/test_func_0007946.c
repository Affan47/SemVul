InitializeInput(void)
{
	memset(joy_readbit,0,sizeof(joy_readbit));
	memset(joy,0,sizeof(joy));
	LastStrobe = 0;

	if(GameInfo->type==GIT_VSUNI)
	{
		SetReadHandler(0x4016,0x4016,VSUNIRead0);
		SetReadHandler(0x4017,0x4017,VSUNIRead1);
	}
	else
		SetReadHandler(0x4016,0x4017,JPRead);

	SetWriteHandler(0x4016,0x4016,B4016);


	SetInputStuff(0);
	SetInputStuff(1);
	SetInputStuffFC();
}
