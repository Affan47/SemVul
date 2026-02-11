H5D__current_cache_size_test(hid_t did, size_t *nbytes_used, int *nused)
{
    H5D_t	*dset;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE


    if(NULL == (dset = (H5D_t *)H5I_object_verify(did, H5I_DATASET)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a dataset")

    if(nbytes_used) {
        HDassert(dset->shared->layout.type == H5D_CHUNKED);
        *nbytes_used = dset->shared->cache.chunk.nbytes_used;
    }

    if(nused) {
        HDassert(dset->shared->layout.type == H5D_CHUNKED);
        *nused = dset->shared->cache.chunk.nused;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
