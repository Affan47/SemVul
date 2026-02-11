NDS_Init( void) {
#endif
     nds.ARM9Cycle = 0;
     nds.ARM7Cycle = 0;
     nds.cycles = 0;
     MMU_Init();
     nds.nextHBlank = 3168;
     nds.VCount = 0;
     nds.lignerendu = FALSE;

     if (Screen_Init(GFXCORE_DUMMY) != 0)
        return -1;

 #ifdef GDB_STUB
     armcpu_new(&NDS_ARM7,1, arm7_mem_if, arm7_ctrl_iface);
     armcpu_new(&NDS_ARM9,0, arm9_mem_if, arm9_ctrl_iface);
#else
	 armcpu_new(&NDS_ARM7,1);
     armcpu_new(&NDS_ARM9,0);
#endif

     if (SPU_Init(SNDCORE_DUMMY, 735) != 0)
        return -1;

#ifdef EXPERIMENTAL_WIFI
	 WIFI_Init(&wifiMac) ;
#endif

     return 0;
}
