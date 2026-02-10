const_get_coll_prop(VMG_ vm_prop_id_t prop,
                                          vm_val_t *retval,
                                          const vm_val_t *self_val,
                                          vm_obj_id_t *src_obj,
                                          uint *argc)
{
    uint func_idx;


    *src_obj = VM_INVALID_OBJ;


    func_idx = G_meta_table
               ->prop_to_vector_idx(metaclass_reg_->get_reg_idx(), prop);


    if ((this->*func_table_[func_idx])(vmg_ retval, self_val, argc))
        return TRUE;


    return FALSE;
}
