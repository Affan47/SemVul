UD_rereg_traverse(const char UNUSED * link_name, hid_t cur_group,
    const void UNUSED *udata, size_t UNUSED udata_size, hid_t lapl_id)
{
    hid_t ret_value;

    if((ret_value = H5Oopen(cur_group, REREG_TARGET_NAME, lapl_id)) < 0) TEST_ERROR

    return ret_value;

error:
    return -1;
}
