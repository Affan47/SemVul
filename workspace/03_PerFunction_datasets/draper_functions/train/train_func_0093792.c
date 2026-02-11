error(ParserControl *parm, parseUnion *stateUnion)
{
	parseUnion lvalp ={0};
	ct = localLex((parseUnion*)&stateUnion->xtokErrorResp, parm);
	if(ct == XTOK_ERROR) {
		setError(parm, &stateUnion->xtokErrorResp);
		ct = localLex((parseUnion*)&stateUnion->xtokErrorResp, parm);
		if(ct == ZTOK_ERROR) {
		}
		else {
			parseError("ZTOK_ERROR", ct, parm);
		}
	}
	else {
		parseError("XTOK_ERROR", ct, parm);
	}
}
