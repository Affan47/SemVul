cl_engine_set_num(struct cl_engine *engine, enum cl_engine_field field, long long num)
{
    if(!engine)
	return CL_ENULLARG;


    switch(field) {
	case CL_ENGINE_MAX_SCANSIZE:
	    engine->maxscansize = num;
	    break;
	case CL_ENGINE_MAX_FILESIZE:
	    engine->maxfilesize = num;
	    break;
	case CL_ENGINE_MAX_RECURSION:
	    if(!num) {
		cli_warnmsg("MaxRecursion: the value of 0 is not allowed, using default: %u\n", CLI_DEFAULT_MAXRECLEVEL);
		engine->maxreclevel = CLI_DEFAULT_MAXRECLEVEL;
	    } else
		engine->maxreclevel = num;
	    break;
	case CL_ENGINE_MAX_FILES:
	    engine->maxfiles = num;
	    break;
	case CL_ENGINE_MAX_EMBEDDEDPE:
	    if(num < 0) {
		cli_warnmsg("MaxEmbeddedPE: negative values are not allowed, using default: %u\n", CLI_DEFAULT_MAXEMBEDDEDPE);
		engine->maxembeddedpe = CLI_DEFAULT_MAXEMBEDDEDPE;
	    } else
		engine->maxembeddedpe = num;
	    break;
	case CL_ENGINE_MAX_HTMLNORMALIZE:
	    if(num < 0) {
		cli_warnmsg("MaxHTMLNormalize: negative values are not allowed, using default: %u\n", CLI_DEFAULT_MAXHTMLNORMALIZE);
		engine->maxhtmlnormalize = CLI_DEFAULT_MAXHTMLNORMALIZE;
	    } else
		engine->maxhtmlnormalize = num;
	    break;
	case CL_ENGINE_MAX_HTMLNOTAGS:
	    if(num < 0) {
		cli_warnmsg("MaxHTMLNoTags: negative values are not allowed, using default: %u\n", CLI_DEFAULT_MAXHTMLNOTAGS);
		engine->maxhtmlnotags = CLI_DEFAULT_MAXHTMLNOTAGS;
	    } else
		engine->maxhtmlnotags = num;
	    break;
	case CL_ENGINE_MAX_SCRIPTNORMALIZE:
	    if(num < 0) {
		cli_warnmsg("MaxScriptNormalize: negative values are not allowed, using default: %u\n", CLI_DEFAULT_MAXSCRIPTNORMALIZE);
		engine->maxscriptnormalize = CLI_DEFAULT_MAXSCRIPTNORMALIZE;
	    } else
		engine->maxscriptnormalize = num;
	    break;
	case CL_ENGINE_MAX_ZIPTYPERCG:
	    if(num < 0) {
		cli_warnmsg("MaxZipTypeRcg: negative values are not allowed, using default: %u\n", CLI_DEFAULT_MAXZIPTYPERCG);
		engine->maxziptypercg = CLI_DEFAULT_MAXZIPTYPERCG;
	    } else
		engine->maxziptypercg = num;
	    break;
	case CL_ENGINE_MIN_CC_COUNT:
	    engine->min_cc_count = num;
	    break;
	case CL_ENGINE_MIN_SSN_COUNT:
	    engine->min_ssn_count = num;
	    break;
	case CL_ENGINE_DB_OPTIONS:
	case CL_ENGINE_DB_VERSION:
	case CL_ENGINE_DB_TIME:
	    cli_warnmsg("cl_engine_set_num: The field is read only\n");
	    return CL_EARG;
	case CL_ENGINE_AC_ONLY:
	    engine->ac_only = num;
	    break;
	case CL_ENGINE_AC_MINDEPTH:
	    engine->ac_mindepth = num;
	    break;
	case CL_ENGINE_AC_MAXDEPTH:
	    engine->ac_maxdepth = num;
	    break;
	case CL_ENGINE_KEEPTMP:
	    engine->keeptmp = num;
	    break;
	case CL_ENGINE_FORCETODISK:
	    if(num)
	        engine->forcetodisk = 1;
	    else
	        engine->forcetodisk = 0;
	    break;
	case CL_ENGINE_BYTECODE_SECURITY:
	    if (engine->dboptions & CL_DB_COMPILED) {
		cli_errmsg("cl_engine_set_num: CL_ENGINE_BYTECODE_SECURITY cannot be set after engine was compiled\n");
		return CL_EARG;
	    }
	    engine->bytecode_security = num;
	    break;
	case CL_ENGINE_BYTECODE_TIMEOUT:
	    engine->bytecode_timeout = num;
	    break;
	case CL_ENGINE_BYTECODE_MODE:
	    if (engine->dboptions & CL_DB_COMPILED) {
		cli_errmsg("cl_engine_set_num: CL_ENGINE_BYTECODE_MODE cannot be set after engine was compiled\n");
		return CL_EARG;
	    }
	    if (num == CL_BYTECODE_MODE_OFF) {
		cli_errmsg("cl_engine_set_num: CL_BYTECODE_MODE_OFF is not settable, use dboptions to turn off!\n");
		return CL_EARG;
	    }
	    engine->bytecode_mode = num;
	    if (num == CL_BYTECODE_MODE_TEST)
		cli_infomsg(NULL, "bytecode engine in test mode\n");
	    break;
	default:
	    cli_errmsg("cl_engine_set_num: Incorrect field number\n");
	    return CL_EARG;
    }

    return CL_SUCCESS;
}
