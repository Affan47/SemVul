H5P_file_image_info_del(hid_t UNUSED prop_id, const char UNUSED *name, size_t UNUSED size, void *value)
{
    H5FD_file_image_info_t info;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    if(value) {
        info = *(H5FD_file_image_info_t *)value;


        HDassert(((info.buffer != NULL) && (info.size > 0)) ||
                 ((info.buffer == NULL) && (info.size == 0)));

        if(info.buffer && info.size > 0) {

            if(info.callbacks.image_free) {
                if(info.callbacks.image_free(info.buffer, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_CLOSE, info.callbacks.udata) < 0)
		    HGOTO_ERROR(H5E_RESOURCE, H5E_CANTFREE, FAIL, "image_free callback failed")
            }
            else
                free(info.buffer);
        }


        if(info.callbacks.udata) {
            if(NULL == info.callbacks.udata_free)
                HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "udata_free not defined")

            if(info.callbacks.udata_free(info.callbacks.udata) < 0)
	        HGOTO_ERROR(H5E_RESOURCE, H5E_CANTFREE, FAIL, "udata_free callback failed")
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
