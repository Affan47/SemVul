H5Aget_storage_size(hid_t attr_id)
{
    H5A_t	*attr;
    hsize_t	ret_value;

    FUNC_ENTER_API(0)
    H5TRACE1("h", "i", attr_id);


    if(NULL == (attr = (H5A_t *)H5I_object_verify(attr_id, H5I_ATTR)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, 0, "not an attribute")


    ret_value = attr->shared->data_size;

done:
    FUNC_LEAVE_API(ret_value)
}
