RAMBO1_init(void)
{
	int x;

        for(x=0;x<11;x++)
         DRegs[x]=~0;
        cmd=0;
        mir=0;
	if(!nomirror)
         setmirror(1);
        Synco();
        GameHBIRQHook=RAMBO1_hb;
        MapIRQHook=RAMBO1_IRQHook;
        GameStateRestore=RAMBO1_Restore;
        SetWriteHandler(0x8000,0xffff,RAMBO1_write);

	AddExState(Rambo_StateRegs, ~0, 0, 0);
}
