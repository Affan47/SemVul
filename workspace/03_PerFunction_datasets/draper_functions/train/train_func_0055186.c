getp_proptype(VMG_ vm_obj_id_t self,
                             vm_val_t *retval, uint *argc,
                             vm_prop_id_t, vm_obj_id_t *)
{
    vm_val_t val;
    vm_prop_id_t prop;
    vm_obj_id_t source_obj;
    static CVmNativeCodeDesc desc(1);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    G_interpreter->pop_prop(vmg_ &val);
    prop = val.val.prop;


    if (!get_prop(vmg_ prop, &val, self, &source_obj, 0))
    {

        retval->set_nil();
    }
    else
    {

        retval->set_datatype(vmg_ &val);
    }


    return TRUE;
}
