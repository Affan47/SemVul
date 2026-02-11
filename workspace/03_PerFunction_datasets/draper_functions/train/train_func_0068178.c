cvt_to_bignum(VMG_ vm_obj_id_t self, vm_val_t *val) const
{

    if (val->typ == VM_INT)
    {


        G_stk->push()->set_obj(self);


        val->set_obj(create(vmg_ FALSE, val->val.intval, 32));


        G_stk->discard();
    }


    if (val->typ != VM_OBJ
        || (vm_objp(vmg_ val->val.obj)->get_metaclass_reg()
            != metaclass_reg_))
    {

        return FALSE;
    }


    return TRUE;
}
