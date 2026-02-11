sq_rawset(HSQUIRRELVM v,SQInteger idx)
{
	SQObjectPtr &self = stack_get(v, idx);
	if(type(v->GetUp(-2)) == OT_NULL) return sq_throwerror(v, _SC("null key"));
	switch(type(self)) {
	case OT_TABLE:
		_table(self)->NewSlot(v->GetUp(-2), v->GetUp(-1));
		v->Pop(2);
		return SQ_OK;
	break;
	case OT_CLASS:
		_class(self)->NewSlot(_ss(v), v->GetUp(-2), v->GetUp(-1),false);
		v->Pop(2);
		return SQ_OK;
	break;
	case OT_INSTANCE:
		if(_instance(self)->Set(v->GetUp(-2), v->GetUp(-1))) {
			v->Pop(2);
			return SQ_OK;
		}
	break;
	case OT_ARRAY:
		if(v->Set(self, v->GetUp(-2), v->GetUp(-1),false)) {
			v->Pop(2);
			return SQ_OK;
		}
	break;
	default:
		v->Pop(2);
		return sq_throwerror(v, _SC("rawset works only on array/table/class and instance"));
	}
	v->Raise_IdxError(v->GetUp(-2));return SQ_ERROR;
}
