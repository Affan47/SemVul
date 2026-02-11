cim(ParserControl *parm, parseUnion *stateUnion)
{
	parseUnion lvalp = {0};
	ct = localLex(stateUnion, parm);
	if(ct == XTOK_CIM) {
		message(parm, (parseUnion*)&stateUnion->xtokMessage);
		ct = localLex(stateUnion, parm);
		if(ct == ZTOK_CIM) {
		}
		else {
			parseError("ZTOK_CIM", ct, parm);
		}
	}
	else {
		parseError("XTOK_CIM", ct, parm);
	}
}
