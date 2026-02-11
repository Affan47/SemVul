mod_run(void)
{
    if ( myports_string ) {
	WRLOCK_TP_CONFIG ;
	nmyports = parse_myports(myports_string, &myports[0], NMYPORTS);
	verb_printf("%s will use %d ports\n", module_name, nmyports);
	UNLOCK_TP_CONFIG ;
    }
    return(MOD_CODE_OK);
}
