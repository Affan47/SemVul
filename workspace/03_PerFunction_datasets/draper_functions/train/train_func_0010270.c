module_load( char *apath )
{
	module.handle = 0;

	module_check();

	if( atexit( module_clean ) )
		msglog( MSG_FATAL, "could not register module cleanup method" );

	if( lt_dlinit() )
		msglog( MSG_FATAL, "module_load: lt_dlinit: %s", lt_dlerror() );

	if( ! ( module.handle = lt_dlopenext( module.mod_path ) ) )
		msglog( MSG_FATAL, "module open error: %s", lt_dlerror() );

	mod_init = module_symbol( SYMBOL_MODULE_INIT );
	mod_dir = module_symbol( SYMBOL_MODULE_DIR );
	mod_dowork = module_symbol( SYMBOL_MODULE_DOWORK );
	mod_clean = module_symbol( SYMBOL_MODULE_CLEAN );

	if( ! ( modinfo = mod_init( module.mod_subopt, apath ) ) )
		msglog( MSG_FATAL, "could not initialize module" );

    	if( modinfo->protocol != MODULE_PROTOCOL_SUPPORTED)
		msglog( MSG_FATAL, "required protocol '%d', " \
			"module protocol '%d' not supported",
		 	MODULE_PROTOCOL_SUPPORTED, modinfo->protocol);

	if( ! modinfo->name )
		msglog( MSG_FATAL, "missing module name info" );

	msglog( MSG_INFO, "module %s loaded from %s",
			modinfo->name, module.mod_path );
}
