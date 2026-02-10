H5IMmake_image_8bit( hid_t loc_id,
                           const char *dset_name,
                           hsize_t width,
                           hsize_t height,
                           const unsigned char *buf )
{
    hsize_t  dims[IMAGE8_RANK];


    dims[0] = height;
    dims[1] = width;


    if ( H5LTmake_dataset( loc_id, dset_name, IMAGE8_RANK, dims, H5T_NATIVE_UCHAR, buf ) < 0)
        return -1;


    if ( H5LTset_attribute_string( loc_id, dset_name, "CLASS", IMAGE_CLASS ) < 0)
        return -1;


    if ( H5LTset_attribute_string( loc_id, dset_name, "IMAGE_VERSION", IMAGE_VERSION ) < 0)
        return -1;


    if ( H5LTset_attribute_string( loc_id, dset_name, "IMAGE_SUBCLASS", "IMAGE_INDEXED" ) < 0)
        return -1;

    return 0;
}
