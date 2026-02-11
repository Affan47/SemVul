ParseInstanceBinary (const char* pCur,DOM* p_pcOut,bool p_bBE)
{
	ai_assert(NULL != pCur && NULL != p_pcOut);

	DefaultLogger::get()->debug("PLY::DOM::ParseInstanceBinary() begin");

	if(!p_pcOut->ParseHeader(pCur,&pCur,true))
	{
		DefaultLogger::get()->debug("PLY::DOM::ParseInstanceBinary() failure");
		return false;
	}
	if(!p_pcOut->ParseElementInstanceListsBinary(pCur,&pCur,p_bBE))
	{
		DefaultLogger::get()->debug("PLY::DOM::ParseInstanceBinary() failure");
		return false;
	}
	DefaultLogger::get()->debug("PLY::DOM::ParseInstanceBinary() succeeded");
	return true;
}
