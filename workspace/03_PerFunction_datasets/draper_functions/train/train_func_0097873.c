globus_l_gass_copy_gass_transfer_cancel_callback(
    void * callback_arg,
    globus_gass_transfer_request_t request)
{
    globus_gass_transfer_request_status_t status;
    globus_object_t *                     err;
    globus_i_gass_copy_cancel_t *         cancel_info
	= (globus_i_gass_copy_cancel_t *) callback_arg;

#ifdef GLOBUS_I_GASS_COPY_DEBUG
	globus_libc_fprintf(stderr,
            "starting _gass_transfer_cancel_callback()\n");
#endif

    status = globus_gass_transfer_request_get_status(request);

    if (status != GLOBUS_SUCCESS)
    {
        err = globus_error_construct_string(
              GLOBUS_GASS_COPY_MODULE,
              GLOBUS_NULL,
              "[%s]: gass_transfer_request_status: %d",
                     "globus_gass_transfer_fail",
                     status);
        globus_i_gass_copy_set_error(cancel_info->handle, err);
    }

    globus_l_gass_copy_generic_cancel(cancel_info);
}
