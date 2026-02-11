slapi_be_gettype(Slapi_Backend *be)
{
	const char *r= NULL;
	if (be->be_state != BE_STATE_DELETED)
	{
	    r= be->be_type;
	}
    return r;
}
