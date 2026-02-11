proc_hash(VALUE self)
{
    st_index_t hash;
    rb_proc_t *proc;
    GetProcPtr(self, proc);
    hash = rb_hash_start((st_index_t)proc->block.iseq);
    hash = rb_hash_uint(hash, (st_index_t)proc->envval);
    hash = rb_hash_uint(hash, (st_index_t)proc->block.lfp >> 16);
    hash = rb_hash_end(hash);
    return LONG2FIX(hash);
}
