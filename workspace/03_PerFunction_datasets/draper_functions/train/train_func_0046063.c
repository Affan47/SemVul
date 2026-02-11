FCEUSS_LoadFP_old(EMUFILE* is, ENUM_SSLOADPARAMS params)
{


	int x;
	uint8 header[16];
	int stateversion;
	char* fn=0;


	{
		FCEUMOV_PreLoad();
	}
    is->fread((char*)&header,16);
	if(memcmp(header,"FCS",3))
	{
		return(0);
	}
	if(header[3] == 0xFF)
	{
		stateversion = FCEU_de32lsb(header + 8);
	}
	else
	{
		stateversion=header[3] * 100;
	}


	x=ReadStateChunks(is,*(uint32*)(header+4));


	if(read_sfcpuc && stateversion<9500)
	{
		X.IRQlow=0;
	}
	if(GameStateRestore)
	{
		GameStateRestore(stateversion);
	}
	if(x)
	{
		FCEUPPU_LoadState(stateversion);
		FCEUSND_LoadState(stateversion);
		x=FCEUMOV_PostLoad();
	}
	if(fn)
	{


		free(fn);
	}

	return(x);
}
