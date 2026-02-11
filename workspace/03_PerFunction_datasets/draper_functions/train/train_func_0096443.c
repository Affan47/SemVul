init_tcl_variables(Tcl_Interp *interp)
{
	char savename[32];
	char savetime[32];

	printstring(savename, "%14.14lu-%8.8lu", (unsigned long)time(NULL), (unsigned long)getpid());
	printstring(savetime, "%d", setup.voice.recordtime);

	if (!MYMKVAR("vbox_var_bindir"   , BINDIR                 )) returnerror();
	if (!MYMKVAR("vbox_var_savename"	, savename               )) returnerror();
	if (!MYMKVAR("vbox_var_rectime"	, savetime               )) returnerror();
	if (!MYMKVAR("vbox_var_spooldir"	, setup.spool            )) returnerror();
	if (!MYMKVAR("vbox_var_checknew", setup.voice.checknewpath)) returnerror();
	if (!MYMKVAR("vbox_msg_standard"	, setup.voice.standardmsg)) returnerror();
	if (!MYMKVAR("vbox_msg_beep"		, setup.voice.beepmsg    )) returnerror();
	if (!MYMKVAR("vbox_msg_timeout"	, setup.voice.timeoutmsg )) returnerror();
	if (!MYMKVAR("vbox_caller_id"		, setup.voice.callerid   )) returnerror();
	if (!MYMKVAR("vbox_caller_phone"	, setup.voice.phone      )) returnerror();
	if (!MYMKVAR("vbox_caller_name"	, setup.voice.name       )) returnerror();
	if (!MYMKVAR("vbox_user_name"		, setup.users.name       )) returnerror();
	if (!MYMKVAR("vbox_user_home"		, setup.users.home       )) returnerror();

	if (!MYMKVAR("vbox_flag_standard", setup.voice.domessage ? "TRUE" : "FALSE")) returnerror();
	if (!MYMKVAR("vbox_flag_beep"    , setup.voice.dobeep    ? "TRUE" : "FALSE")) returnerror();
	if (!MYMKVAR("vbox_flag_timeout" , setup.voice.dotimeout ? "TRUE" : "FALSE")) returnerror();
	if (!MYMKVAR("vbox_flag_record"	, setup.voice.dorecord  ? "TRUE" : "FALSE")) returnerror();

	returnok();
}
