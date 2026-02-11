IfIncrRefCount(PILInterface*eifinfo, int plusminus)
{
	if(DEBUGPLUGIN) {
		PILLog(PIL_DEBUG, "IfIncrRefCount(%d + %d )"
		,	eifinfo->refcnt, plusminus);
	}
	eifinfo->refcnt += plusminus;
	if (eifinfo->refcnt <= 0) {
		eifinfo->refcnt = 0;

		RemoveAPILInterface(eifinfo);
		return 0;
	}
	return eifinfo->refcnt;
}
