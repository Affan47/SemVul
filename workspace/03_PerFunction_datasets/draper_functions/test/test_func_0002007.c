getp_remove_element(VMG_ vm_obj_id_t self,
                                      vm_val_t *retval, uint *argc)
{
    vm_val_t *del_val;
    static CVmNativeCodeDesc desc(1);
    size_t src;
    size_t dst;
    size_t old_cnt;


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    del_val = G_stk->get(0);


    retval->set_obj(self);
    G_stk->push(retval);


    old_cnt = get_element_count();


    for (src = dst = 0 ; src < old_cnt ; ++src)
    {
        vm_val_t ele_val;


        get_element(src, &ele_val);


        if (!ele_val.equals(vmg_ del_val))
        {


            if (dst != src)
                set_element_undo(vmg_ self, dst, &ele_val);


            ++dst;
        }
    }


    if (dst != old_cnt)
        set_element_count_undo(vmg_ self, dst);


    G_stk->discard(2);


    return TRUE;
}
