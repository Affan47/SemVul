notify_new_savept()
{
    CVmObjPageEntry **pg;
    CVmObjPageEntry *entry;
    size_t i;
    size_t j;
    vm_obj_id_t id;


    for (id = 0, i = pages_used_, pg = pages_ ; i > 0 ; ++pg, --i)
    {

        for (j = VM_OBJ_PAGE_CNT, entry = *pg ; j > 0 ; --j, ++entry, ++id)
        {

            if (!entry->free_)
            {


                entry->in_undo_ = TRUE;


                entry->get_vm_obj()->notify_new_savept();
            }
        }
    }
}
