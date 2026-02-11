unload()
{
	#if !NSF_EMU_APU_ONLY
	{
		delete vrc6;
		vrc6  = 0;

		delete namco;
		namco = 0;

		delete fme7;
		fme7  = 0;
	}
	#endif

	rom.clear();
	Music_Emu::unload();
}
