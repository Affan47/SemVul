gc_pass_continue(VMG_ int trace_transient)
{
    int cnt;


    for (cnt = VM_GC_WORK_INCREMENT ;
         cnt != 0 && gc_queue_head_ != VM_INVALID_OBJ ; --cnt)
    {
        vm_obj_id_t cur;
        CVmObjPageEntry *entry;


        cur = gc_queue_head_;


        entry = get_entry(cur);


        gc_queue_head_ = entry->next_obj_;


        if (trace_transient || !entry->transient_)
            entry->get_vm_obj()->mark_refs(vmg_ entry->reachable_);
    }


    return gc_queue_head_ != VM_INVALID_OBJ;
}
