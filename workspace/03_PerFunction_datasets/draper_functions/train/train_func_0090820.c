H5S_set_extent(H5S_t *space, const hsize_t *size)
{
    unsigned u;
    htri_t ret_value = FALSE;

    FUNC_ENTER_NOAPI(H5S_set_extent, FAIL)


    HDassert(space && H5S_SIMPLE == H5S_GET_EXTENT_TYPE(space));
    HDassert(size);


    for(u = 0; u < space->extent.rank; u++) {
        if(space->extent.size[u] != size[u]) {

            if(space->extent.max && H5S_UNLIMITED != space->extent.max[u] &&
                     space->extent.max[u] < size[u])
                 HGOTO_ERROR(H5E_DATASPACE, H5E_BADVALUE, FAIL, "dimension cannot exceed the existing maximal size")


            ret_value = TRUE;
        }
    }


    if(ret_value)
        if(H5S_set_extent_real(space, size) < 0)
             HGOTO_ERROR(H5E_DATASPACE, H5E_CANTSET, FAIL, "failed to change dimension size(s)")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
