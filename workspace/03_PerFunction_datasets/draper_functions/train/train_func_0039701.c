H5S_mpio_all_type(const H5S_t *space, size_t elmt_size,
    MPI_Datatype *new_type, int *count, hbool_t *is_derived_type)
{
    hsize_t	total_bytes;
    hssize_t	snelmts;
    hsize_t	nelmts;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(space);


    if((snelmts = (hssize_t)H5S_GET_EXTENT_NPOINTS(space)) < 0)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "src dataspace has invalid selection")
    H5_ASSIGN_OVERFLOW(nelmts, snelmts, hssize_t, hsize_t);

    total_bytes = (hsize_t)elmt_size * nelmts;


    *new_type = MPI_BYTE;
    H5_ASSIGN_OVERFLOW(*count, total_bytes, hsize_t, int);
    *is_derived_type = FALSE;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
