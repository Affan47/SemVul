H5O_size(const H5F_t UNUSED *f, const H5O_t *oh, size_t *size_ptr)
{
    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5O_size)


    HDassert(oh);
    HDassert(size_ptr);


    *size_ptr = (size_t)H5O_SIZEOF_HDR(oh) + oh->chunk0_size;

    FUNC_LEAVE_NOAPI(SUCCEED)
}
