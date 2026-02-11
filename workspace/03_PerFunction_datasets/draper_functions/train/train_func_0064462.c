misc2_create_type(void)
{
    hid_t type, type_tmp;
    herr_t ret;

    type_tmp = H5Tcopy (H5T_C_S1);
    CHECK(type_tmp, FAIL, "H5Tcopy");

    ret = H5Tset_size(type_tmp, H5T_VARIABLE);
    CHECK(ret, FAIL, "H5Tset_size");

    type = H5Tcreate(H5T_COMPOUND, sizeof(misc2_struct));
    CHECK(type, FAIL, "H5Tcreate");

    ret = H5Tinsert(type, "string", offsetof(misc2_struct, string), type_tmp);
    CHECK(ret, FAIL, "H5Tinsert");

    ret = H5Tclose(type_tmp);
    CHECK(ret, FAIL, "H5Tclose");

    return type;
}
