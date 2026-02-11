ResetGameLoaded(void)
{
        if(FCEUGameInfo) CloseGame();
        GameStateRestore=0;
        PPU_hook=0;
        GameHBIRQHook=0;
        if(GameExpSound.Kill)
         GameExpSound.Kill();
        memset(&GameExpSound,0,sizeof(GameExpSound));
        MapIRQHook=0;
        MMC5Hack=0;
        PAL&=1;
	pale=0;
}
