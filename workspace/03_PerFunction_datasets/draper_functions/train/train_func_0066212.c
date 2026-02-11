mca_base_pvar_handle_stop (mca_base_pvar_handle_t *handle)
{
    int ret;


    if (!mca_base_pvar_handle_is_running (handle) || mca_base_pvar_is_continuous (handle->pvar)) {
        return OPAL_ERR_NOT_SUPPORTED;
    }

    ret = mca_base_pvar_handle_update (handle);
    if (OPAL_SUCCESS != ret) {
        return ret;
    }


    (void) mca_base_pvar_notify (handle, MCA_BASE_PVAR_HANDLE_STOP, NULL);


    handle->started = false;

    return OPAL_SUCCESS;
}
