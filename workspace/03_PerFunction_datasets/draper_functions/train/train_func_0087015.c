EndCall()
{
	SquirrelObject ret;
	if(_CallState >= 0) {
		SQInteger oldtop = sq_gettop(_VM);
		SQInteger nparams = _CallState;
		_CallState = -1;
		if(SQ_SUCCEEDED(sq_call(_VM,nparams,SQTrue,SQ_CALL_RAISE_ERROR))) {
			ret.AttachToStackObject(-1);
			sq_pop(_VM,2);
		}else {
			sq_settop(_VM,oldtop-(nparams+1));
			throw SquirrelError();
		}

	}
	return ret;
}
