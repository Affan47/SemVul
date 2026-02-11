H5T_get_array_dims(const H5T_t *dt, hsize_t dims[])
{
    unsigned u;
    int	ret_value;

    FUNC_ENTER_NOAPI(H5T_get_array_dims, FAIL)

    HDassert(dt);
    HDassert(dt->shared->type == H5T_ARRAY);


    if(dims)
        for(u = 0; u < dt->shared->u.array.ndims; u++)
            dims[u] = dt->shared->u.array.dim[u];


    ret_value = dt->shared->u.array.ndims;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
