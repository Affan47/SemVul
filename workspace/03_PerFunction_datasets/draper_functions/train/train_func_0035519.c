upgradedn_free_list(struct upgradedn_attr **ud_list)
{
    struct upgradedn_attr *ptr = *ud_list;

    while (ptr) {
        struct upgradedn_attr *next = ptr->ud_next;
        slapi_ch_free_string(&ptr->ud_type);
        slapi_ch_free_string(&ptr->ud_value);
        slapi_ch_free((void **)&ptr);
        ptr = next;
    }
    *ud_list = NULL;
    return;
}
