sq_setdebughook(HSQUIRRELVM v)
{
	SQObject o = stack_get(v,-1);
	if(sq_isclosure(o) || sq_isnativeclosure(o) || sq_isnull(o)) {
		v->_debughook = o;
		v->Pop();
	}
}
