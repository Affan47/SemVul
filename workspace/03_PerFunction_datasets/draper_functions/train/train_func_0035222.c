H5Z_can_apply_scaleoffset(hid_t UNUSED dcpl_id, hid_t type_id, hid_t UNUSED space_id)
{
    const H5T_t	*type;
    H5T_class_t dtype_class;
    H5T_order_t dtype_order;
    htri_t ret_value = TRUE;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL == (type = (H5T_t *)H5I_object_verify(type_id, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype")


    if((dtype_class = H5T_get_class(type, TRUE)) == H5T_NO_CLASS)
	HGOTO_ERROR(H5E_PLINE, H5E_BADTYPE, FAIL, "bad datatype class")


    if(H5T_get_size(type) == 0)
	HGOTO_ERROR(H5E_PLINE, H5E_BADTYPE, FAIL, "bad datatype size")

    if(dtype_class == H5T_INTEGER || dtype_class == H5T_FLOAT) {

        if((dtype_order = H5T_get_order(type)) == H5T_ORDER_ERROR)
	    HGOTO_ERROR(H5E_PLINE, H5E_BADTYPE, FAIL, "can't retrieve datatype endianness order")


        if(dtype_order != H5T_ORDER_LE && dtype_order != H5T_ORDER_BE)
            HGOTO_ERROR(H5E_PLINE, H5E_BADTYPE, FALSE, "bad datatype endianness order")
    } else
        HGOTO_ERROR(H5E_PLINE, H5E_BADTYPE, FALSE, "datatype class not supported by scaleoffset")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
