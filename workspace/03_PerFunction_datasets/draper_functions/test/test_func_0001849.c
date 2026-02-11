print_reference_type(h5tools_str_t *buffer, hid_t type, int UNUSED ind)
{
    if (H5T_REFERENCE!=H5Tget_class(type)) return FALSE;

    if (H5Tequal(type, H5T_STD_REF_OBJ)==TRUE) {
        h5tools_str_append(buffer, "object reference");
    }
    else if (H5Tequal(type, H5T_STD_REF_DSETREG)==TRUE) {
        h5tools_str_append(buffer, "dataset region reference");
    }
    else {
        h5tools_str_append(buffer, "%lu-byte unknown reference",
                (unsigned long)H5Tget_size(type));
    }

    return TRUE;
}
