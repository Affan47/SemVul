get_prop(VMG_ vm_prop_id_t prop, vm_val_t *retval,
                               vm_obj_id_t self, vm_obj_id_t *source_obj,
                               uint *argc)
{
    vm_val_t self_val;


    self_val.set_obj(self);


    if (const_get_coll_prop(vmg_ prop, retval, &self_val, source_obj, argc))
    {
        *source_obj = metaclass_reg_->get_class_obj(vmg0_);
        return TRUE;
    }


    return CVmObject::get_prop(vmg_ prop, retval, self, source_obj, argc);
}
