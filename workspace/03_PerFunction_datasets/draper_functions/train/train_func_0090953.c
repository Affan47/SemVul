FCEU_QSimpleCommand(int cmd)
{
	if(FCEUnetplay)
		FCEUNET_SendCommand(cmd, 0);
	else
	{
		if(!FCEUMOV_Mode(MOVIEMODE_TASEDITOR))
			FCEU_DoSimpleCommand(cmd);
		if(FCEUMOV_Mode(MOVIEMODE_RECORD|MOVIEMODE_TASEDITOR))
			FCEUMOV_AddCommand(cmd);
	}
}
