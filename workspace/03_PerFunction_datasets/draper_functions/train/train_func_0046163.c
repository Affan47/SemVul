add_undo_rec(VMG_ vm_obj_id_t self, dict_undo_rec *rec)
{
    vm_val_t val;


    val.set_empty();
    if (!G_undo->add_new_record_ptr_key(vmg_ self, rec, &val))
    {


        t3free(rec);
    }
}
