oshmem_proc_destruct(oshmem_proc_t* proc)
{


    OBJ_RELEASE( proc->proc_convertor);


    OPAL_THREAD_LOCK(&oshmem_proc_lock);
    opal_list_remove_item(&oshmem_proc_list, (opal_list_item_t*) proc);
    OPAL_THREAD_UNLOCK(&oshmem_proc_lock);
}
