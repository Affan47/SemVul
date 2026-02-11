cli_loadldb(FILE *fs, struct cl_engine *engine, unsigned int *signo, unsigned int options, struct cli_dbio *dbio, const char *dbname)
{
	char buffer[CLI_DEFAULT_LSIG_BUFSIZE + 1], *buffer_cpy = NULL;
	unsigned int line = 0, sigs = 0;
	int ret;


    if((ret = cli_initroots(engine, options)))
	return ret;

    if(engine->ignored)
	if(!(buffer_cpy = cli_malloc(sizeof(buffer)))) {
        cli_errmsg("cli_loadldb: Can't allocate memory for buffer_cpy\n");
	    return CL_EMEM;
    }
    while(cli_dbgets(buffer, sizeof(buffer), fs, dbio)) {
	line++;
	if(buffer[0] == '#')
	    continue;
	sigs++;
	cli_chomp(buffer);

	if(engine->ignored)
	    strcpy(buffer_cpy, buffer);
	ret = load_oneldb(buffer,
			  engine->pua_cats && (options & CL_DB_PUA_MODE) && (options & (CL_DB_PUA_INCLUDE | CL_DB_PUA_EXCLUDE)),
			  engine, options, dbname, line, &sigs, 0, buffer_cpy, NULL);
	if (ret)
	    break;
    }
    if(engine->ignored)
	free(buffer_cpy);

    if(!line) {
	cli_errmsg("Empty database file\n");
	return CL_EMALFDB;
    }

    if(ret) {
	cli_errmsg("Problem parsing database at line %u\n", line);
	return ret;
    }

    if(signo)
	*signo += sigs;

    return CL_SUCCESS;
}
