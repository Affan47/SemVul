for_each_gen(VMG_ vm_obj_id_t self,
                               vm_val_t *retval, uint *argc,
                               int pass_key_to_cb)
{
    const vm_val_t *func_val;
    size_t idx;
    static CVmNativeCodeDesc desc(1);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    func_val = G_stk->get(0);


    G_interpreter->push_obj(vmg_ self);


    retval->set_nil();


    for (idx = 0 ; idx < get_element_count() ; ++idx)
    {

        push_element(vmg_ idx);


        if (pass_key_to_cb)
            G_stk->push()->set_int(idx + 1);


        G_interpreter->call_func_ptr(vmg_ func_val, pass_key_to_cb ? 2 : 1,
                                     "Vector.forEach", 0);
    }


    G_stk->discard(2);


    return TRUE;
}
