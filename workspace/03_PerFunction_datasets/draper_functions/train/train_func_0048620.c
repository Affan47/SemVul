getp_for_each_word(VMG_ vm_obj_id_t self, vm_val_t *retval,
                                   uint *argc)
{
    static CVmNativeCodeDesc desc(1);
    vm_val_t *cb_val;
    for_each_word_enum_cb_ctx ctx;


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    cb_val = G_stk->get(0);


    G_stk->push()->set_obj(self);


    ctx.vmg = VMGLOB_ADDR;
    ctx.cb_val = cb_val;
    get_ext()->hashtab_->safe_enum_entries(for_each_word_enum_cb, &ctx);


    G_stk->discard(2);


    retval->set_nil();


    return TRUE;
}
