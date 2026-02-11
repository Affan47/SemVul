image_memcpy(void *dest, const void *src, size_t size, H5FD_file_image_op_t file_image_op,
    void *_udata)
{
    H5LT_file_image_ud_t *udata = (H5LT_file_image_ud_t *)_udata;


    if (!(udata->flags & H5LT_FILE_IMAGE_DONT_COPY))
        goto out;

    switch(file_image_op) {
        case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_SET:
            if (dest != udata->fapl_image_ptr)
                goto out;
            if (src != udata->app_image_ptr)
                goto out;
            if (size != udata->fapl_image_size)
                goto out;
            if (size != udata->app_image_size)
                goto out;
            if (udata->fapl_ref_count == 0)
                goto out;
            break;

        case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_COPY:
            if (dest != udata->fapl_image_ptr)
                goto out;
            if (src != udata->fapl_image_ptr)
                goto out;
            if (size != udata->fapl_image_size)
                goto out;
            if (udata->fapl_ref_count < 2)
                goto out;
            break;

        case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_GET:
            goto out;

        case H5FD_FILE_IMAGE_OP_FILE_OPEN:
            if (dest != udata->vfd_image_ptr)
                goto out;
            if (src != udata->fapl_image_ptr)
                goto out;
            if (size != udata->vfd_image_size)
                goto out;
            if (size != udata->fapl_image_size)
                goto out;
            if (udata->fapl_ref_count == 0)
                goto out;
            if (udata->vfd_ref_count != 1)
                goto out;
            break;


	case H5FD_FILE_IMAGE_OP_NO_OP:
	case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_CLOSE:
	case H5FD_FILE_IMAGE_OP_FILE_RESIZE:
	case H5FD_FILE_IMAGE_OP_FILE_CLOSE:
        default:
            goto out;
    }

    return(dest);

out:
    return NULL;
}
