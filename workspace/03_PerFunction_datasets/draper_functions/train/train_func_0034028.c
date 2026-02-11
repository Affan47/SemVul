H5FD_log_set_eoa(H5FD_t *_file, H5FD_mem_t UNUSED type, haddr_t addr)
{
    H5FD_log_t	*file = (H5FD_log_t*)_file;
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI(H5FD_log_set_eoa, FAIL)

    file->eoa = addr;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
