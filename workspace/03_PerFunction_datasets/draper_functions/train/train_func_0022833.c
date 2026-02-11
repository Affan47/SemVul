returnValue(ParserControl *parm, parseUnion *stateUnion)
{
	parseUnion lvalp ={0};
	CMPIType  t;
	CMPIValue val;
	CMPIInstance *inst;
	ct = localLex((parseUnion*)&stateUnion->xtokReturnValue, parm);
	if(ct == XTOK_RETVALUE) {
		returnValueData(parm, (parseUnion*)&stateUnion->xtokReturnValue.data);
		if(stateUnion->xtokReturnValue.data.type == CMPI_ref) {
			t = CMPI_ref;
			val = str2CMPIValue(t, NULL, &stateUnion->xtokReturnValue.data.ref);
		}
		else if(stateUnion->xtokReturnValue.data.value.type == typeValue_Instance) {
			t = CMPI_instance;
			inst = native_new_CMPIInstance(NULL,NULL);
			setInstNsAndCn(inst,getNameSpaceChars(parm->requestObjectPath),stateUnion->xtokReturnValue.data.value.data.inst->className);
			setInstProperties(inst, &stateUnion->xtokReturnValue.data.value.data.inst->properties);
			val.inst = inst;
		}
		else {
			t = stateUnion->xtokReturnValue.type;
			if (t == CMPI_null) {
				t = guessType(stateUnion->xtokReturnValue.data.value.data.value);
			}
			val = str2CMPIValue(t, stateUnion->xtokReturnValue.data.value.data.value, NULL);
		}
		simpleArrayAdd(parm->respHdr.rvArray, (CMPIValue*)&val, t);
		ct = localLex((parseUnion*)&stateUnion->xtokReturnValue, parm);
		if(ct == ZTOK_RETVALUE) {
		}
		else {
			parseError("ZTOK_RETVALUE", ct, parm);
		}
	}
	else {
		parseError("XTOK_RETVALUE", ct, parm);
	}
}
