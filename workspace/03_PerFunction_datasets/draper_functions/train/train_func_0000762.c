globus_l_gass_copy_ftp_read_callback(
    void *                          callback_arg,
    globus_ftp_client_handle_t *    handle,
    globus_object_t *               error,
    globus_byte_t *                 bytes,
    globus_size_t                   nbytes,
    globus_off_t                    offset,
    globus_bool_t		    eof)
{
    globus_gass_copy_handle_t * copy_handle
	= (globus_gass_copy_handle_t *) callback_arg;
    globus_gass_copy_state_t * state
        = copy_handle->state;

    globus_bool_t last_data= GLOBUS_FALSE;

#ifdef GLOBUS_I_GASS_COPY_DEBUG
    globus_libc_fprintf(stderr,
	"ftp_read_callback(): start, n_pending: %d, nbytes: %d, offset: %"GLOBUS_OFF_T_FORMAT", eof: %d\n",
	state->source.n_pending, nbytes, offset, eof);
#endif

    if(error == GLOBUS_SUCCESS)
    {
	last_data = eof;
	if(eof)
	{
#ifdef GLOBUS_I_GASS_COPY_DEBUG
	  globus_libc_fprintf(stderr,
	      "ftp_read_callback(): source TARGET_DONE, nbytes: %d, offset: %"GLOBUS_OFF_T_FORMAT", eof: %d\n",
	      nbytes, offset, eof);
#endif


	    if((copy_handle->status != GLOBUS_GASS_COPY_STATUS_FAILURE) &&
	       (copy_handle->status < GLOBUS_GASS_COPY_STATUS_READ_COMPLETE))
		copy_handle->status = GLOBUS_GASS_COPY_STATUS_READ_COMPLETE;
	}
    }
    else
    {
#ifdef GLOBUS_I_GASS_COPY_DEBUG
	globus_libc_fprintf(stderr, "ftp_read_callback: was passed an ERROR\n");
#endif
	{
	    if(!state->cancel)
	    {
		globus_i_gass_copy_set_error(copy_handle, error);
		state->cancel = GLOBUS_I_GASS_COPY_CANCEL_TRUE;
		copy_handle->status = GLOBUS_GASS_COPY_STATUS_FAILURE;
                state->source.data.ftp.data_err = copy_handle->err;
	    }
	    else
	    {
	        globus_mutex_lock(&(state->source.mutex));
		state->source.n_pending--;
		globus_mutex_unlock(&(state->source.mutex));
		return;
	    }

	}
    }


    globus_l_gass_copy_generic_read_callback(
        copy_handle,
        bytes,
        nbytes,
        offset,
	last_data);
}
