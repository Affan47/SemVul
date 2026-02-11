image_malloc(size_t size, H5FD_file_image_op_t file_image_op, void *_udata)
{
    H5LT_file_image_ud_t *udata = (H5LT_file_image_ud_t *)_udata;
    void * return_value = NULL;


    if (!(udata->flags & H5LT_FILE_IMAGE_DONT_COPY))
        goto out;

    switch ( file_image_op ) {

        case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_SET:
            if (udata->app_image_ptr == NULL)
                goto out;
            if (udata->app_image_size != size)
                goto out;
            if (udata->fapl_image_ptr != NULL)
                goto out;
            if (udata->fapl_image_size != 0)
                goto out;
            if (udata->fapl_ref_count != 0)
                goto out;

            udata->fapl_image_ptr = udata->app_image_ptr;
            udata->fapl_image_size = udata->app_image_size;
            return_value = udata->fapl_image_ptr;
            udata->fapl_ref_count++;
	    break;

	case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_COPY:
            if (udata->fapl_image_ptr == NULL)
                goto out;
            if (udata->fapl_image_size != size)
                goto out;
            if (udata->fapl_ref_count == 0)
                goto out;

            return_value = udata->fapl_image_ptr;
            udata->fapl_ref_count++;
	    break;

        case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_GET:
            goto out;

        case H5FD_FILE_IMAGE_OP_FILE_OPEN:

            if (udata->vfd_image_ptr != NULL)
                goto out;
            if (udata->vfd_image_size != 0)
                goto out;
            if (udata->vfd_ref_count != 0)
                goto out;
            if (udata->fapl_image_ptr == NULL)
                goto out;
            if (udata->fapl_image_size != size)
                goto out;
            if (udata->fapl_ref_count == 0)
                goto out;

            udata->vfd_image_ptr = udata->fapl_image_ptr;
 	    udata->vfd_image_size = size;
            udata->vfd_ref_count++;
            return_value = udata->vfd_image_ptr;
            break;


	case H5FD_FILE_IMAGE_OP_NO_OP:
	case H5FD_FILE_IMAGE_OP_PROPERTY_LIST_CLOSE:
	case H5FD_FILE_IMAGE_OP_FILE_RESIZE:
	case H5FD_FILE_IMAGE_OP_FILE_CLOSE:
        default:
            goto out;
    }

    return(return_value);

out:
    return NULL;
}
