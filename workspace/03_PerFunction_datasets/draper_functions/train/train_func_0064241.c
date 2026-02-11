modules_init(void)
{
#ifndef STATIC_MODULES
	if(lt_dlinit())
	{
		ilog(L_MAIN, "lt_dlinit failed");
		exit(0);
	}

	modlist = rb_malloc(sizeof(struct module) * (MODS_INCREMENT));
	mod_add_cmd(&modload_msgtab);
	mod_add_cmd(&modunload_msgtab);
	mod_add_cmd(&modreload_msgtab);
	mod_add_cmd(&modrestart_msgtab);
	mod_add_cmd(&modlist_msgtab);
#endif

}
