H5FL_malloc(size_t mem_size)
{
    void *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL==(ret_value=H5MM_malloc(mem_size))) {

        if(H5FL_garbage_coll()<0)
            HGOTO_ERROR(H5E_RESOURCE, H5E_CANTGC, NULL, "garbage collection failed during allocation")


        if(NULL==(ret_value=H5MM_malloc(mem_size)))
            HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed for chunk")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
