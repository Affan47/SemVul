_stream_writeblob(HSQUIRRELVM v)
{
	SQUserPointer data;
	SQInteger size;
	SETUP_STREAM(v);
	if(SQ_FAILED(sqstd_getblob(v,2,&data)))
		return sq_throwerror(v,_SC("invalid parameter"));
	size = sqstd_getblobsize(v,2);
	if(self->Write(data,size) != size)
		return sq_throwerror(v,_SC("io error"));
	sq_pushinteger(v,size);
	return 1;
}
