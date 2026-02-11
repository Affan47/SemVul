CL_Init (void)
{
	if (dedicated->integer)
		return;


	CL_gameFont = &_CL_gameFont;
	FNT_AutoInit( CL_gameFont , "freesans" , 0 , 65 , 8 , 48 );
	CL_gameFont->faceVar = Cvar_Get( "fnt_game" , "orbitron" , CVAR_ARCHIVE );
	CL_gameFont->sizeVar = Cvar_Get( "fnt_game_size" , "0" , CVAR_ARCHIVE );
	FNT_AutoRegister( CL_gameFont );

	CL_centerFont = &_CL_centerFont;
	FNT_AutoInit( CL_centerFont , "freesans" , 0 , 45 , 16 , 64 );
	CL_centerFont->faceVar = CL_gameFont->faceVar;
	CL_centerFont->sizeVar = Cvar_Get( "fnt_center_size" , "0" , CVAR_ARCHIVE );
	FNT_AutoRegister( CL_centerFont );

	CL_consoleFont = &_CL_consoleFont;
	FNT_AutoInit( CL_consoleFont , "freesans" , 0 , 52 , 8 , 48 );
	CL_consoleFont->faceVar = Cvar_Get( "fnt_console" , "freemono" , CVAR_ARCHIVE );
	CL_consoleFont->sizeVar = Cvar_Get( "fnt_console_size" , "0" , CVAR_ARCHIVE );
	FNT_AutoRegister( CL_consoleFont );

	CL_menuFont = &_CL_menuFont;
	FNT_AutoInit( CL_menuFont , "freesans" , 0 , 48 , 8 , 48 );
	CL_menuFont->faceVar = Cvar_Get( "fnt_menu" , "freesans" , CVAR_ARCHIVE );
	CL_menuFont->sizeVar = Cvar_Get( "fnt_menu_size" , "0" , CVAR_ARCHIVE );
	FNT_AutoRegister( CL_menuFont );


	CON_Initialise( );

	VID_Init ();
	S_Init ();

	V_Init ();

	net_message.data = net_message_buffer;
	net_message.maxsize = sizeof(net_message_buffer);

	M_Init ();

	SCR_Init ();
	cls.disable_screen = true;

	CL_InitLocal ();
	IN_Init ();

	FS_ExecAutoexec ();
	Cbuf_Execute ();

	if ( name && name->string[0] )
	{
		ValidatePlayerName( name->string, (strlen(name->string)+1) );
	}
}
