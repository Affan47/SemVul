ir_commit_i(IndexReader *ir)
{
    if (ir->has_changes) {
        if (NULL == ir->deleter && NULL != ir->store) {


            ir->set_deleter_i(ir, deleter_new(ir->sis, ir->store));
        }
        if (ir->is_owner) {
            char curr_seg_fn[MAX_FILE_PATH];
            mutex_lock(&ir->store->mutex);

            sis_curr_seg_file_name(curr_seg_fn, ir->store);

            ir->commit_i(ir);
            sis_write(ir->sis, ir->store, ir->deleter);

            if (ir->deleter) deleter_delete_file(ir->deleter, curr_seg_fn);

            mutex_unlock(&ir->store->mutex);

            if (NULL != ir->write_lock) {

                ir->write_lock->release(ir->write_lock);
                close_lock(ir->write_lock);
                ir->write_lock = NULL;
            }
        }
        else {
            ir->commit_i(ir);
        }
    }
    ir->has_changes = false;
}
