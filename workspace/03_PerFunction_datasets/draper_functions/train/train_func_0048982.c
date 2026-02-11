init(void* args)
{
	bool lastplugin = *((bool*)args);
	if (!lastplugin) {

		String r(cv["useragentregexp"]);
		if (r.length() > 0) {
#ifdef DGDEBUG
			std::cout<<"useragent regexp: "<<r<<std::endl;
#endif
			ua_match.comp(r.toCharArray());
		} else {

#ifdef DGDEBUG
			std::cout<<"no useragent regular expression; defaulting to .*"<<std::endl;
#endif
			alwaysmatchua = true;
		}
		if (!readStandardLists())
			return -1;
	}
#ifdef DGDEBUG
	else
		std::cout<<"Fallback DM plugin; no matching options loaded"<<std::endl;
#endif
	return 0;
}
