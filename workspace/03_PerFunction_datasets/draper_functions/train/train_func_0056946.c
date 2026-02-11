globus_gass_copy_set_buffer_length(
    globus_gass_copy_handle_t * handle,
    int length)
{
    globus_object_t * err;
    static char * myname="globus_gass_copy_set_buffer_length";
    if (handle)
    {
	handle->buffer_length = length;
	return GLOBUS_SUCCESS;
    }
    else
    {
	err = globus_error_construct_string(
	    GLOBUS_GASS_COPY_MODULE,
	    GLOBUS_NULL,
	    "[%s]: BAD_PARAMETER, handle is NULL",
	    myname);

	return globus_error_put(err);
    }
}
