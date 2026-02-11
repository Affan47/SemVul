CL_RestartFilesystem( qboolean execAutoexec )
{
    connstate_t	cls_state;

    if ( cls.state == ca_uninitialized ) {
        FS_Restart();
		if (execAutoexec) {
			FS_ExecConfig("autoexec.cfg");
			Cbuf_Execute();
		}
        return;
    }

    Com_DPrintf( "CL_RestartFilesystem()\n" );


    cls_state = cls.state;
    if ( cls.state == ca_active ) {

    }

	S_Shutdown();
	VID_Shutdown();

    FS_Restart();

	if (execAutoexec) {
		silentSubsystem = CVAR_SYSTEM_VIDEO|CVAR_SYSTEM_SOUND;
		FS_ExecConfig("autoexec.cfg");
		Cbuf_Execute();
		silentSubsystem = 0;
	}

#ifndef VID_INITFIRST
	S_Init();
	VID_Restart_f();
	VID_CheckChanges();
#else
	VID_Restart_f();
	VID_CheckChanges();
	S_Init();
#endif

    if ( cls_state == ca_disconnected ) {

    } else if ( cls_state > ca_connected ) {
		memset(cl.sound_precache, 0, sizeof(cl.sound_precache));
		CL_RegisterSounds();
        CL_PrepRefresh();
    }


    cls.state = cls_state;
}
