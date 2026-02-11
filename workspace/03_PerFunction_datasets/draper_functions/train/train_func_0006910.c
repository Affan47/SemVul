H5O_efl_total_size (H5O_efl_t *efl)
{
    hsize_t	ret_value = 0, tmp;

    FUNC_ENTER_NOAPI_NOINIT

    if(efl->nused > 0 && H5O_EFL_UNLIMITED == efl->slot[efl->nused - 1].size)
	ret_value = H5O_EFL_UNLIMITED;
    else {
        size_t		u;

	for(u = 0; u < efl->nused; u++, ret_value = tmp) {
	    tmp = ret_value + efl->slot[u].size;
	    if(tmp <= ret_value)
		HGOTO_ERROR(H5E_EFL, H5E_OVERFLOW, 0, "total external storage size overflowed");
	}
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
