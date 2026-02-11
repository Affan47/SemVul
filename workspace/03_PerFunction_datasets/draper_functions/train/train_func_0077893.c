LoadGame(const char *path)
{
	FCEUGI *tmp;

	CloseGame();
        if(!(tmp=FCEUI_LoadGame(path)))
	 return 0;
	CurGame=tmp;
        ParseGI(tmp);
        RefreshThrottleFPS();

        if(!DriverInitialize(tmp))
         return(0);
	if(soundrecfn)
	{
	 if(!FCEUI_BeginWaveRecord(soundrecfn))
	 {
 	  free(soundrecfn);
	  soundrecfn=0;
	 }
	}
	isloaded=1;
	#ifdef EXTGUI
	if(eoptions&EO_AUTOHIDE) GUI_Hide(1);
	#endif

	FCEUD_NetworkConnect();
	return 1;
}
