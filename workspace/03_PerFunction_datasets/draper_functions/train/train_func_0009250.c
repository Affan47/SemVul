H5FD_fapl_close(hid_t driver_id, void *fapl)
{
    H5FD_class_t	*driver = NULL;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    if(driver_id > 0) {
        if(NULL == (driver = (H5FD_class_t *)H5I_object(driver_id)))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a driver ID")


        if(H5FD_pl_close(driver_id, driver->fapl_free, fapl) < 0)
            HGOTO_ERROR(H5E_VFL, H5E_CANTINIT, FAIL, "driver fapl_free request failed")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
