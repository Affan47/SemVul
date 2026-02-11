oshmem_proc_finalize(void)
{
    opal_list_item_t *item;


    oshmem_proc_group_finalize();


    while (opal_list_get_end(&oshmem_proc_list)
            != (item = opal_list_get_first(&oshmem_proc_list))) {
        OBJ_RELEASE(item);
    }
    OBJ_RELEASE( oshmem_shmem_local_convertor);

    OBJ_DESTRUCT(&oshmem_proc_list);
    OBJ_DESTRUCT(&oshmem_proc_lock);

    return OSHMEM_SUCCESS;
}
