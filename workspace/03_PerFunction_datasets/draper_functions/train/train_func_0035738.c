mca_base_param_dump_release(opal_list_t *info)
{
    opal_list_item_t *item;

    while (NULL != (item = opal_list_remove_first(info))) {
        OBJ_RELEASE(item);
    }

    OBJ_RELEASE(info);

    return OPAL_SUCCESS;
}
