save_file_cb(void *ctx0, CVmHashEntry *entry0)
{
    save_file_ctx *ctx = (save_file_ctx *)ctx0;
    CVmHashEntryDict *entry = (CVmHashEntryDict *)entry0;
    vm_dict_entry *cur;
    uint cnt;


    VMGLOB_PTR(ctx->vmg);


    ctx->fp->write_int2(entry->getlen());
    ctx->fp->write_bytes(entry->getstr(), entry->getlen());


    for (cnt = 0, cur = entry->get_head() ; cur != 0 ; cur = cur->nxt_)
    {


        if (G_obj_table->is_obj_persistent(cur->obj_))
            ++cnt;
    }


    if (cnt == 0)
        return;


    ++ctx->cnt;


    ctx->fp->write_int2(cnt);


    for (cur = entry->get_head() ; cur != 0 ; cur = cur->nxt_)
    {

        if (G_obj_table->is_obj_persistent(cur->obj_))
        {

            ctx->fp->write_int4((long)cur->obj_);
            ctx->fp->write_int2((int)cur->prop_);
        }
    }
}
