find_proc(ompi_proc_t *proc)
{
    ompi_common_ofacm_base_proc_t *ret = NULL;
    opal_list_item_t *item;
    opal_list_t *list = &ompi_common_ofacm_oob.all_procs;

    for (item = opal_list_get_first(list);
            item != opal_list_get_end(list);
            item = opal_list_get_next(item)) {
        if (proc == ((ompi_common_ofacm_base_proc_t *)item)->proc_ompi){
            ret = (ompi_common_ofacm_base_proc_t *)item;
        }
    }
    return ret;
}
