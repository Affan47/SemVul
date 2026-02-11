compute_hash(const char *str, size_t len) const
    {
        vm_val_t val;
        vm_val_t cobj_val;
        VMGLOB_PTR(globals_);


        G_stk->push()->set_obj(CVmObjString::create(vmg_ FALSE, str, len));


        cobj_val.set_obj(comparator_);
        G_interpreter->get_prop(vmg_ 0, &cobj_val, G_predef->calc_hash_prop,
                                &cobj_val, 1);


        val = *G_interpreter->get_r0();


        if (val.typ == VM_INT)
        {

            return val.val.intval;
        }
        else
        {

            err_throw(VMERR_BAD_TYPE_BIF);
            AFTER_ERR_THROW(return FALSE;)
        }
    }
