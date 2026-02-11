H5Oclose(hid_t object_id)
{
    herr_t       ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE1("e", "i", object_id);


    switch(H5I_get_type(object_id)) {
        case H5I_GROUP:
        case H5I_DATATYPE:
        case H5I_DATASET:
            if(H5I_object(object_id) == NULL)
                HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "not a valid object")
            if(H5I_dec_app_ref(object_id) < 0)
                HGOTO_ERROR(H5E_OHDR, H5E_CANTRELEASE, FAIL, "unable to close object")
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
            HGOTO_ERROR(H5E_ARGS, H5E_CANTRELEASE, FAIL, "not a valid file object ID (dataset, group, or datatype)")
        break;
    }

done:
    FUNC_LEAVE_API(ret_value)
}
