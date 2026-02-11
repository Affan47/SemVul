domainlist_match(const struct cl_engine* engine,char* real_url,const char* display_url,const struct pre_fixup_info* pre_fixup,int hostOnly)
{
	const char* info;
	int rc = engine->domainlist_matcher ? regex_list_match(engine->domainlist_matcher,real_url,display_url,hostOnly ? pre_fixup : NULL,hostOnly,&info,0) : 0;
	return rc;
}
