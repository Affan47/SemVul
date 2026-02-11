for_each_word_enum_cb(void *ctx0, CVmHashEntry *entry0)
{
    for_each_word_enum_cb_ctx *ctx = (for_each_word_enum_cb_ctx *)ctx0;
    CVmHashEntryDict *entry = (CVmHashEntryDict *)entry0;
    size_t list_idx;
    vm_obj_id_t str_obj;


    VMGLOB_PTR(ctx->vmg);


    str_obj = CVmObjString::create(vmg_ FALSE,
                                   entry->getstr(), entry->getlen());


    for (list_idx = 0 ; ; ++list_idx)
    {
        vm_dict_entry *p;
        size_t i;


        for (i = 0, p = entry->get_head() ; i < list_idx && p != 0 ;
             p = p->nxt_, ++i) ;


        if (p == 0)
            break;


        G_stk->push()->set_propid(p->prop_);


        G_stk->push()->set_obj(str_obj);


        G_stk->push()->set_obj(p->obj_);


        G_interpreter->call_func_ptr(vmg_ ctx->cb_val, 3,
                                     "Dictionary.forEachWord", 0);
    }
}
