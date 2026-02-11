H5LT_get_attribute_disk( hid_t loc_id,
                               const char *attr_name,
                               void *attr_out )
{

    hid_t attr_id;
    hid_t attr_type;

    if(( attr_id = H5Aopen(loc_id, attr_name, H5P_DEFAULT)) < 0)
        return -1;

    if((attr_type = H5Aget_type(attr_id)) < 0)
        goto out;

    if(H5Aread(attr_id, attr_type, attr_out) < 0)
        goto out;

    if(H5Tclose(attr_type) < 0)
        goto out;

    if ( H5Aclose( attr_id ) < 0 )
        return -1;;

    return 0;

out:
    H5Tclose( attr_type );
    H5Aclose( attr_id );
    return -1;
}
