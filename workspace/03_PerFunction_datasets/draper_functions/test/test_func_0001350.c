CompileSound(int keyword, int isvowel)
{
	int addr;
	int value = 0;
	char path[N_ITEM_STRING];
	static int sound_instns[] = {i_FMT, i_WAV, i_VWLSTART, i_VWLENDING, i_WAVADD};

	NextItemBrackets(tSTRING,2);
	strcpy(path, item_string);
	if(item_terminator == ',')
	{
		if((keyword == kVOWELSTART) || (keyword == kVOWELENDING))
		{
			value = NextItemBrackets(tSIGNEDNUMBER,1);
			if(value > 127)
			{
				value = 127;
				error("Parameter > 127",NULL);
			}
			if(value < -128)
			{
				value = -128;
				error("Parameter < -128",NULL);
			}
		}
		else
		{
			value = NextItemBrackets(tNUMBER,1);
			if(value > 255)
			{
				value = 255;
				error("Parameter > 255",NULL);
			}
		}
	}
	addr = LoadDataFile(path, isvowel);
	addr = addr / 4;

	*prog_out++ = sound_instns[keyword-kFMT] + ((value & 0xff) << 4) + ((addr >> 16) & 0xf);
	*prog_out++ = addr & 0xffff;
	return(0);
}
