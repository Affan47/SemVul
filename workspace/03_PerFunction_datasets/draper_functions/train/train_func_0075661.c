get_prop(VMG_ vm_prop_id_t prop, vm_val_t *retval,
                        vm_obj_id_t self, vm_obj_id_t *source_obj, uint *argc)
{
    uint func_idx;


    func_idx = G_meta_table
               ->prop_to_vector_idx(metaclass_reg_->get_reg_idx(), prop);


    *source_obj = metaclass_reg_->get_class_obj(vmg0_);


    return (this->*func_table_[func_idx])(vmg_ self, retval, argc,
                                          prop, source_obj);
}
