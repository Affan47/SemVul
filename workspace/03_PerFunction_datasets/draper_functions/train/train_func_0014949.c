sq_setparamscheck(HSQUIRRELVM v,SQInteger nparamscheck,const SQChar *typemask)
{
	SQObject o = stack_get(v, -1);
	if(!sq_isnativeclosure(o))
		return sq_throwerror(v, _SC("native closure expected"));
	SQNativeClosure *nc = _nativeclosure(o);
	nc->_nparamscheck = nparamscheck;
	if(typemask) {
		SQIntVec res;
		if(!CompileTypemask(res, typemask))
			return sq_throwerror(v, _SC("invalid typemask"));
		nc->_typecheck.copy(res);
	}
	else {
		nc->_typecheck.resize(0);
	}
	if(nparamscheck == SQ_MATCHTYPEMASKSTRING) {
		nc->_nparamscheck = nc->_typecheck.size();
	}
	return SQ_OK;
}
