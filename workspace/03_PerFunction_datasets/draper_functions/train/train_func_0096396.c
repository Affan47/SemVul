sq_getfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval)
{
	SQObjectPtr &self = stack_get(v,idx);
	const SQChar *name = NULL;
	if(type(self) == OT_CLOSURE) {
		if(_closure(self)->_outervalues.size()>nval) {
			v->Push(_closure(self)->_outervalues[nval]);
			SQFunctionProto *fp = _funcproto(_closure(self)->_function);
			SQOuterVar &ov = fp->_outervalues[nval];
			name = _stringval(ov._name);
		}
	}
	return name;
}
