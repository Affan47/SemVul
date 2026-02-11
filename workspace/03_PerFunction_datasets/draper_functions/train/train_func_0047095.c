ReadObject(HSQUIRRELVM v,SQUserPointer up,SQREADFUNC read,SQObjectPtr &o)
{
	SQObjectType t;
	_CHECK_IO(SafeRead(v,read,up,&t,sizeof(SQObjectType)));
	switch(t){
	case OT_STRING:{
		SQInteger len;
		_CHECK_IO(SafeRead(v,read,up,&len,sizeof(SQInteger)));
		_CHECK_IO(SafeRead(v,read,up,_ss(v)->GetScratchPad(rsl(len)),rsl(len)));
		o=SQString::Create(_ss(v),_ss(v)->GetScratchPad(-1),len);
				   }
		break;
	case OT_INTEGER:{
		SQInteger i;
		_CHECK_IO(SafeRead(v,read,up,&i,sizeof(SQInteger))); o = i; break;
					}
	case OT_FLOAT:{
		SQFloat f;
		_CHECK_IO(SafeRead(v,read,up,&f,sizeof(SQFloat))); o = f; break;
				  }
	case OT_NULL:
		o=_null_;
		break;
	default:
		v->Raise_Error(_SC("cannot serialize a %s"),IdType2Name(t));
		return false;
	}
	return true;
}
