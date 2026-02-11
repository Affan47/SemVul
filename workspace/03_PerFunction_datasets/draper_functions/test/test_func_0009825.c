H5O_get_loc(hid_t object_id)
{
    H5O_loc_t   *ret_value;

    FUNC_ENTER_NOAPI_NOINIT

    switch(H5I_get_type(object_id)) {
        case H5I_GROUP:
            if(NULL == (ret_value = H5O_OBJ_GROUP->get_oloc(object_id)))
                HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, NULL, "unable to get object location from group ID")
            break;

        case H5I_DATASET:
            if(NULL == (ret_value = H5O_OBJ_DATASET->get_oloc(object_id)))
                HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, NULL, "unable to get object location from dataset ID")
            break;

        case H5I_DATATYPE:
            if(NULL == (ret_value = H5O_OBJ_DATATYPE->get_oloc(object_id)))
                HGOTO_ERROR(H5E_OHDR, H5E_CANTGET, NULL, "unable to get object location from datatype ID")
            break;

        case H5I_UNINIT:
        case H5I_BADID:
        case H5I_FILE:
        case H5I_DATASPACE:
        case H5I_ATTR:
        case H5I_REFERENCE:
        case H5I_VFL:
        case H5I_GENPROP_CLS:
        case H5I_GENPROP_LST:
        case H5I_ERROR_CLASS:
        case H5I_ERROR_MSG:
        case H5I_ERROR_STACK:
        case H5I_NTYPES:
        default:
            HGOTO_ERROR(H5E_OHDR, H5E_BADTYPE, NULL, "invalid object type")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
