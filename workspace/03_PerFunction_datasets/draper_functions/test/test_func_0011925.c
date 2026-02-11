H5S_all_bounds(const H5S_t *space, hsize_t *start, hsize_t *end)
{
    unsigned rank;
    unsigned i;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    HDassert(space);
    HDassert(start);
    HDassert(end);


    rank = space->extent.rank;


    for(i = 0; i < rank; i++) {
        start[i] = 0;
        end[i] = space->extent.size[i] - 1;
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
