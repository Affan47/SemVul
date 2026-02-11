delete_obj_table(VMG0_)
{
    size_t i;
    vm_image_ptr_page *ip_page;
    vm_image_ptr_page *ip_next;


    post_load_init_table_->delete_all_entries();


    for (i = 0 ; i < pages_used_ ; ++i)
    {
        int j;
        CVmObjPageEntry *entry;


        for (j = 0, entry = pages_[i] ; j < VM_OBJ_PAGE_CNT ; ++j, ++entry)
        {

            if (!entry->free_)
                entry->get_vm_obj()->notify_delete(vmg_ entry->in_root_set_);
        }
    }


    for (i = 0 ; i < pages_used_ ; ++i)
    {

        t3free(pages_[i]);
    }


    t3free(pages_);


    pages_ = 0;
    page_slots_ = 0;
    pages_used_ = 0;


    for (ip_page = image_ptr_head_ ; ip_page != 0 ; ip_page = ip_next)
    {

        ip_next = ip_page->next_;


        t3free(ip_page);
    }


    if (globals_ != 0)
    {
        delete globals_;
        globals_ = 0;
    }


    while (global_var_head_ != 0)
        delete_global_var(global_var_head_);


    delete post_load_init_table_;
    post_load_init_table_ = 0;
}
