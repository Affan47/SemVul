sq_deleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval)
{
	sq_aux_paramscheck(v, 2);
	SQObjectPtr *self;
	_GETSAFE_OBJ(v, idx, OT_TABLE,self);
	SQObjectPtr &key = v->GetUp(-1);
	if(type(key) == OT_NULL) return sq_throwerror(v, _SC("null is not a valid key"));
	SQObjectPtr res;
	if(!v->DeleteSlot(*self, key, res)){
		return SQ_ERROR;
	}
	if(pushval)	v->GetUp(-1) = res;
	else v->Pop(1);
	return SQ_OK;
}
