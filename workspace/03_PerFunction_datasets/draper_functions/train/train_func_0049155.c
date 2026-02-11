qualifier(ParserControl *parm, parseUnion *stateUnion)
{
	parseUnion lvalp={0};
	ct = localLex((parseUnion*)&stateUnion->xtokQualifier, parm);
	if(ct == XTOK_QUALIFIER) {
		ct = localLex(&lvalp, parm);
		dontLex = 1;
		if(ct == XTOK_VALUE || ct == XTOK_VALUEARRAY) {
			dontLex = 1;
			qualifierData(parm, (parseUnion*)&lvalp.xtokQualifierData);
			stateUnion->xtokQualifier.data = lvalp.xtokQualifierData;
			if(lvalp.xtokQualifierData.isArray) {
				stateUnion->xtokQualifier.type |= CMPI_ARRAY;
			}
		}
		ct = localLex((parseUnion*)&stateUnion->xtokQualifier, parm);
		if(ct == ZTOK_QUALIFIER) {
		}
		else {
			parseError("ZTOK_QUALIFIER or XTOK_VALUE or XTOK_VALUEARRAY", ct, parm);
		}
	}
	else {
		parseError("XTOK_QUALIFIER", ct, parm);
	}
}
