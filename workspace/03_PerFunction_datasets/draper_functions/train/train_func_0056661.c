clist_init_io_procs(gx_device_clist *pclist_dev, bool in_memory)
{
#ifdef PACIFY_VALGRIND
    VALGRIND_HG_DISABLE_CHECKING(&clist_io_procs_file_global, sizeof(clist_io_procs_file_global));
    VALGRIND_HG_DISABLE_CHECKING(&clist_io_procs_memory_global, sizeof(clist_io_procs_memory_global));
#endif


    if (in_memory || clist_io_procs_file_global == NULL)
        pclist_dev->common.page_info.io_procs = clist_io_procs_memory_global;
    else
        pclist_dev->common.page_info.io_procs = clist_io_procs_file_global;
}
