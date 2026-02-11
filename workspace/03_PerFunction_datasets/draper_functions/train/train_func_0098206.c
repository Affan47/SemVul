SetInstanceUP(SQUserPointer up)
{
	if(!sq_isinstance(_o)) return FALSE;
	sq_pushobject(SquirrelVM::_VM,_o);
	sq_setinstanceup(SquirrelVM::_VM,-1,up);
	sq_pop(SquirrelVM::_VM,1);
	return TRUE;
}
