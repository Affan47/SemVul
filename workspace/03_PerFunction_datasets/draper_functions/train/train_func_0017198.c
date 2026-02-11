H5LTset_attribute_long( hid_t loc_id,
                              const char *obj_name,
                              const char *attr_name,
                              const long *data,
                              size_t size )
{

    if ( H5LT_set_attribute_numerical( loc_id, obj_name, attr_name, size,
        H5T_NATIVE_LONG, data ) < 0 )
        return -1;

    return 0;

}
