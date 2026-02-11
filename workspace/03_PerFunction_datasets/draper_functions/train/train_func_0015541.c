whitelist_match(const struct cl_engine* engine,char* real_url,const char* display_url,int hostOnly)
{
	const char* info;
	cli_dbgmsg("Phishing: looking up in whitelist: %s:%s; host-only:%d\n",real_url,display_url,hostOnly);
	return	engine->whitelist_matcher ? regex_list_match(engine->whitelist_matcher,real_url,display_url,NULL,hostOnly,&info,1) : 0;
}
