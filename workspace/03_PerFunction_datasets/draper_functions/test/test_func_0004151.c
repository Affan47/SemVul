H5Sget_select_elem_pointlist(hid_t spaceid, hsize_t startpoint,
    hsize_t numpoints, hsize_t buf[])
{
    H5S_t *space;
    herr_t ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "ihh*[a2]h", spaceid, startpoint, numpoints, buf);


    if(NULL == buf)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid pointer")
    if(NULL == (space = (H5S_t *)H5I_object_verify(spaceid, H5I_DATASPACE)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a data space")
    if(H5S_GET_SELECT_TYPE(space) != H5S_SEL_POINTS)
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a point selection")

    ret_value = H5S_get_select_elem_pointlist(space, startpoint, numpoints, buf);

done:
    FUNC_LEAVE_API(ret_value)
}
