SafeWrite(HSQUIRRELVM v,SQWRITEFUNC write,SQUserPointer up,SQUserPointer dest,SQInteger size)
{
	if(write(up,dest,size) != size) {
		v->Raise_Error(_SC("io error (write function failure)"));
		return false;
	}
	return true;
}
