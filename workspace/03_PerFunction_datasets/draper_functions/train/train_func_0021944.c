CORBA_exc_set(CORBA_Environment *env,
		   CORBA_exception_type Major,
		   CORBA_char *Id,
		   CORBA_char *Value)
{
    int ilen,vlen;


    if (env->_major == CORBA_NO_EXCEPTION) {


	ilen = strlen(Id)+1;
	vlen = strlen(Value)+1;


	env->_exc_id = (CORBA_char *) malloc(ilen);
	env->_exc_value = (CORBA_char *) malloc(vlen);


	env->_major = Major;
	strcpy(env->_exc_id,Id);
	strcpy(env->_exc_value,Value);
    }
}
