globus_gass_copy_flush_url_state(
    globus_gass_copy_handle_t * handle,
    char * url)
{
    globus_result_t result;
    globus_url_t url_info;
    globus_object_t * err;
    static char * myname="globus_gass_copy_flush_url_state";

    if(handle != GLOBUS_NULL)
    {
	globus_url_parse(url, &url_info);
	if (   (strcmp(url_info.scheme, "ftp") == 0)
	       || (strcmp(url_info.scheme, "gsiftp") == 0)    )
	{
	    result = globus_ftp_client_handle_flush_url_state(
	                &handle->ftp_handle_2,
	                url);
            if (result == GLOBUS_SUCCESS)
            {
                result = globus_ftp_client_handle_flush_url_state(
                               &handle->ftp_handle,
                               url);
            }
	}
	else
	{
	    err = globus_error_construct_string(
	      GLOBUS_GASS_COPY_MODULE,
	      GLOBUS_NULL,
	      "[%s]: BAD_URL_SCHEME, url: %s, only ftp or gsiftp can be cached",
	      myname,
	      url);
	    return globus_error_put(err);
	}

        globus_url_destroy(&url_info);

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
    return result;
}
