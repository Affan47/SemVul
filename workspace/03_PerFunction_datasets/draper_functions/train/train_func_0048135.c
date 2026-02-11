NEG_OP(SQObjectPtr &trg,const SQObjectPtr &o)
{

	switch(type(o)) {
	case OT_INTEGER:
		trg = -_integer(o);
		return true;
	case OT_FLOAT:
		trg = -_float(o);
		return true;
	case OT_TABLE:
	case OT_USERDATA:
	case OT_INSTANCE:
		if(_delegable(o)->_delegate) {
			Push(o);
			if(CallMetaMethod(_delegable(o), MT_UNM, 1, temp_reg)) {
				trg = temp_reg;
				return true;
			}
		}
	default:break;
	}
	Raise_Error(_SC("attempt to negate a %s"), GetTypeName(o));
	return false;
}
