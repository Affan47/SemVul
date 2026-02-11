globus_gass_copy_attr_init(
    globus_gass_copy_attr_t * attr)
{
    globus_object_t * err;
    static char * myname="globus_gass_copy_attr_init";
    if(attr!=GLOBUS_NULL)
    {
	attr->ftp_attr = GLOBUS_NULL;
	attr->io = GLOBUS_NULL;
	attr->gass_requestattr = GLOBUS_NULL;
	return GLOBUS_SUCCESS;
    }
    else
    {
	err = globus_error_construct_string(
	    GLOBUS_GASS_COPY_MODULE,
	    GLOBUS_NULL,
	    "[%s]: BAD_PARAMETER, attr is NULL",
	    myname);
	return globus_error_put(err);
    }
}
