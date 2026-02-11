getp_to_list(VMG_ vm_obj_id_t self, vm_val_t *retval,
                               uint *argc)
{
    size_t src_cnt;
    size_t dst_cnt;
    size_t start_idx;
    CVmObjList *lst;
    size_t idx;
    uint orig_argc = (argc != 0 ? *argc : 0);
    static CVmNativeCodeDesc desc(0, 2);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    src_cnt = get_element_count();


    if (orig_argc >= 1)
        start_idx = (size_t)CVmBif::pop_int_val(vmg0_);
    else
        start_idx = 1;


    if (start_idx < 1)
        start_idx = 1;


    --start_idx;


    if (orig_argc >= 2)
        dst_cnt = (size_t)CVmBif::pop_int_val(vmg0_);
    else
        dst_cnt = src_cnt;


    if (start_idx >= src_cnt)
    {

        dst_cnt = 0;
    }
    else if (src_cnt - start_idx < dst_cnt)
    {

        dst_cnt = src_cnt - start_idx;
    }


    G_stk->push()->set_obj(self);


    retval->set_obj(CVmObjList::create(vmg_ FALSE, dst_cnt));
    lst = (CVmObjList *)vm_objp(vmg_ retval->val.obj);


    for (idx = 0 ; idx < dst_cnt ; ++idx)
    {
        vm_val_t val;


        get_element(idx + start_idx, &val);


        lst->cons_set_element(idx, &val);
    }


    G_stk->discard();


    return TRUE;
}
